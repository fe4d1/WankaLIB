#!/bin/bash

ROOT=$(cd "$(dirname "$0")" && pwd)
source "$ROOT/config.sh"

BUILD=$ROOT/.build
BIN=$ROOT/.bin
TR=$ROOT/traces
SAVED=$ROOT/.libft_path
UPD=$ROOT/.update
ARGS=("$@")
ARG_PATH=
SELF=
ALL="$PART1 $PART2 $PART3"
CHECKS="files header norm make protos symbols readme"
VALGRIND=1
WHERE=${WHERE:-0}
LOGIN=
FAILS=()
WARNS=0
BUILT=0
SECTION=

STRICT=0
CHK_OK=0
CHK_KO=0
F_RUN=0
F_OK=0

# red and white theme, green for what passes, orange for the score
# W white, B titles, G pass, C pass badge, R fail badge, Y warning,
# O score, M dim, D reset
W=$'\033[1;97m' B=$'\033[1;31m' G=$'\033[1;32m' C=$'\033[1;97;42m'
R=$'\033[1;97;41m' Y=$'\033[31m' O=$'\033[1;38;5;208m'
M=$'\033[2m' D=$'\033[0m'

HELLO=(
	"Warming up valgrind. Hide your leaks."
	"Let's see what malloc thinks of you today."
	"No bonus, no excuses. Everything is mandatory."
	"Copying your libft. The original stays untouched."
)
WIN=(
	"Moulinette would be proud."
	"Not a single byte leaked. Chef's kiss."
	"Push it before something breaks."
	"Clean run. Go grab a coffee."
)
LOSE=(
	"Close. The traces know what you did."
	"malloc can fail. So can we. Try again."
	"KO is just OK read backwards. Go fix it."
	"Read the trace, fix one thing, run again."
)

say() { local a=("$@"); printf "%s" "${a[RANDOM % ${#a[@]}]}"; }

banner()
{
	local line
	printf "\n"
	while IFS= read -r line; do
		printf "  ${W}%s${B}%s${D}\n" "${line:0:33}" "${line:33}"
	done <<'END'
__      __             _          _     ___  ___
\ \    / / __ _  _ _  | |__ __ _ | |   |_ _|| _ )
 \ \/\/ / / _` || ' \ | / // _` || |__  | | | _ \
  \_/\_/  \__,_||_||_||_\_\\__,_||____||___||___/
END
	printf "  ${B}libft tester${D}  ${M}42 Malaga, subject 19.3${D}\n"
}

usage()
{
	cat <<END
usage: ./run.sh [-p libft_path] [-u login] [-n] [-w] [target ...]
       ./run.sh update | clean | reset

./run.sh alone opens the menu and stays open: run things, change the
libft folder, read this help, and leave with q. Your libft is copied
again on every run, so edit it in another tab and just run again.
With targets it runs them once and exits (in a pipe or a script, no
target means all).

libft folder, first one that exists
  -p path, the folder chosen with p in the menu, LIBFT in config.sh,
  the folder that contains the tester, the current folder

quick levels
  soft      function tests without valgrind (fast)
  moderate  norm, Makefile and function tests with valgrind
  strict    everything, and every warning counts as a KO

in the menu only
  p         change the libft folder (it is remembered)
  v         turn valgrind on or off
  w         where: the line of your code that crashes or leaks (on/off)
  u         update the tester (when the menu says there is one)
  q         quit

targets (mix as many as you want, levels included)
  all       everything
  checks   files header norm make protos symbols readme
  files     required files and extra files
  header    42 header of every file (file name, login, mail)
  norm      norminette
  make      Makefile rules, compiler, flags, relink
  protos    prototypes and t_list against the subject
  symbols   forbidden functions, globals, non static helpers
  readme    README.md requirements
  funcs     all function tests
  part1 part2 part3
  ft_split  one function (strlen works too)

output
  every test has a number: ft_atoi  1)OK 2)OK 3)KO
  traces/ft_atoi.txt says why test 3 exists, its code, got and expected

maintenance
  update    download the last version of the tester (git pull)
  clean     delete .build .bin and traces
  reset     put the tester back as in its last commit (asks first)

options
  -p path   libft directory
  -u login  expected login in the 42 headers
  -n        no valgrind (faster)
  -w        where: show the line of your code that crashes or leaks
            (a wrong result has no line, only crashes and memory errors)
END
}

section() { SECTION=$1; printf "\n${B}== %s ==${D}\n" "$1"; }
ok() { printf "  ${G}OK${D}    %s\n" "$1"; CHK_OK=$((CHK_OK + 1)); }
warn()
{
	[ $STRICT = 1 ] && { ko "$1 (warning, strict)"; return; }
	printf "  ${Y}WARN${D}  %s\n" "$1"
	WARNS=$((WARNS + 1))
}
ko()
{
	printf "  ${R}KO${D}    %s" "$1"
	[ -n "$2" ] && printf "  (traces/%s)" "$2"
	printf "\n"
	FAILS+=("$SECTION: $1")
	CHK_KO=$((CHK_KO + 1))
}

is_func() { [[ " $(echo $ALL) " == *" $1 "* ]]; }

prepare()
{
	rm -rf "$BUILD" "$BIN"
	mkdir -p "$BUILD" "$BIN" "$TR"
	find "$LIBFT" -maxdepth 1 -type f ! -name '*.o' ! -name '*.a' \
		-exec cp {} "$BUILD" \;
}

build()
{
	[ $BUILT = 1 ] && return 0
	[ $BUILT = 2 ] && { warn "skipped (make failed)"; return 1; }
	prepare
	if make -C "$BUILD" > "$TR/make.txt" 2>&1 && [ -f "$BUILD/libft.a" ]; then
		BUILT=1
		rm -f "$TR/make.txt"
		return 0
	fi
	BUILT=2
	ko "make failed" make.txt
	return 1
}

check_files()
{
	section files
	local expected="$EXTRA_FILES" f missing=0 top
	for f in $ALL; do expected="$expected $f.c"; done
	for f in $expected; do
		[ -f "$LIBFT/$f" ] || { ko "missing $f"; missing=1; }
	done
	[ $missing = 0 ] && ok "all $(echo $expected | wc -w) required files are there"
	if top=$(git -C "$LIBFT" rev-parse --show-toplevel 2>/dev/null); then
		[ "$top" = "$LIBFT" ] || warn "libft is not at the root of the git repo"
		for f in $(git -C "$LIBFT" ls-files); do
			[[ " $expected " == *" $f "* ]] || ko "extra file tracked in git: $f"
		done
		[ -z "$(git -C "$LIBFT" status --porcelain | grep -vxF "?? ${SELF:-/}/")" ] \
			|| warn "uncommitted changes (only pushed work is graded)"
	else
		warn "not a git repo, cannot check tracked files"
	fi
	for f in $(ls -A "$LIBFT"); do
		[ "$f" = .git ] && continue
		[ "$f" = "$SELF" ] && continue
		[[ " $expected " == *" $f "* ]] && continue
		git -C "$LIBFT" ls-files --error-unmatch "$f" > /dev/null 2>&1 \
			|| warn "extra file in the folder (not tracked): $f"
	done
}

check_header()
{
	section "42 header"
	local f name l bad=0 who mail by authors=""
	for f in "$LIBFT"/Makefile "$LIBFT"/*.c "$LIBFT"/*.h; do
		[ -f "$f" ] || continue
		name=$(basename "$f")
		if ! sed -n 1p "$f" | grep -qE '^(/\*|#) \*{70,} (\*/|#)$'; then
			ko "$name: no 42 header"; bad=1; continue
		fi
		head -11 "$f" | awk 'length($0) != 80 { exit 1 }' \
			|| { ko "$name: header lines are not 80 columns"; bad=1; }
		sed -n 4p "$f" | grep -qF "   $name " \
			|| { ko "$name: file name in header is wrong"; bad=1; }
		l=$(sed -n 6p "$f")
		who=$(echo "$l" | sed -nE 's/.*By: ([^ ]+) <.*/\1/p')
		mail=$(echo "$l" | sed -nE 's/.*By: [^ ]+ <([^ >]+).*/\1/p')
		if [ -z "$who" ] || [[ "$mail" != *@* ]]; then
			ko "$name: bad By line (login <mail>)"; bad=1; continue
		fi
		[[ "$mail" == "$who"@* ]] || warn "$name: mail $mail does not match login $who"
		for l in 8 9; do
			by=$(sed -n ${l}p "$f" | sed -nE 's/.*(Created|Updated): .* by ([^ ]+).*/\2/p')
			[ "$by" = "$who" ] || { ko "$name: line $l login '$by' is not '$who'"; bad=1; }
		done
		authors="$authors$who <$mail>"$'\n'
	done
	authors=$(echo "$authors" | grep . | sort -u)
	[ $bad = 0 ] && ok "header present and file names match"
	if [ "$(echo "$authors" | grep -c .)" -gt 1 ]; then
		ko "more than one author: $(echo $authors)"
	elif [ -n "$authors" ]; then
		ok "author $authors"
		[ -z "$LOGIN" ] || [ "${authors%% *}" = "$LOGIN" ] \
			|| ko "login is ${authors%% *} expected $LOGIN"
	fi
}

check_norm()
{
	section norm
	local out
	command -v norminette > /dev/null || { warn "norminette not installed"; return; }
	out=$(cd "$LIBFT" && norminette *.c *.h 2>&1 | grep -v ': OK!$')
	if [ -z "$out" ]; then
		ok "$(ls "$LIBFT"/*.c "$LIBFT"/*.h | wc -l) files"
	else
		echo "$out" > "$TR/norm.txt"
		ko "$(echo "$out" | grep -c 'Error!$') files with errors" norm.txt
		echo "$out" | sed 's/^/        /'
	fi
}

check_make()
{
	section makefile
	local mk=$BUILD/Makefile r lines n nc fl extra
	prepare
	[ -f "$mk" ] || { ko "no Makefile"; return; }
	for r in all clean fclean re; do
		grep -qE "^$r[[:space:]]*:" "$mk" || ko "rule $r missing"
	done
	grep -qE '^\$\(NAME\)[[:space:]]*:' "$mk" || ko 'rule $(NAME) missing'
	grep -qE '^NAME[[:space:]]*:?=[[:space:]]*libft\.a[[:space:]]*$' "$mk" \
		|| ko "NAME is not libft.a"
	grep -qE 'wildcard|\*\.c' "$mk" && ko "wildcard in Makefile"
	grep -qi libtool "$mk" && ko "libtool is forbidden"
	grep -qE '^bonus[[:space:]]*:' "$mk" && warn "bonus rule but this subject has no bonus"
	r=0
	for fl in "$BUILD"/*.c; do
		cc $FLAGS -c "$fl" -I "$BUILD" -o /dev/null 2>> "$TR/compile.txt" \
			|| { ko "$(basename "$fl") does not compile with $FLAGS" compile.txt; r=1; }
	done
	[ $r = 0 ] && ok "every .c compiles alone with $FLAGS" && rm -f "$TR/compile.txt"

	lines=$(make -C "$BUILD" -n 2> /dev/null \
		| grep -E '(^|[[:space:]/])(cc|gcc|clang)[[:space:]]' | grep -- ' -c')
	n=$(echo "$lines" | grep -c .)
	nc=$(ls "$BUILD"/*.c 2> /dev/null | wc -l)
	if [ "$n" -lt "$nc" ]; then
		ko "make -n shows $n compile lines for $nc .c files"
	else
		echo "$lines" | grep -qvE '^[[:space:]]*cc[[:space:]]' \
			&& ko "compiler must be cc" || ok "compiler is cc"
		r=0
		for fl in $FLAGS; do
			echo "$lines" | grep -qvE -- " $fl( |$)" && { ko "flag $fl missing"; r=1; }
		done
		[ $r = 0 ] && ok "every file compiled with $FLAGS"
		extra=$(echo "$lines" | tr ' ' '\n' | grep '^-' \
			| grep -vxE -- "-c|-o|-I.*|${FLAGS// /|}" | sort -u | tr '\n' ' ')
		[ -n "$extra" ] && warn "extra flags: $extra"
		[[ "$extra" == *std=c99* ]] && ko "-std=c99 is forbidden"
	fi
	make -C "$BUILD" -n 2> /dev/null | grep -qE '(^|[[:space:]/])ar[[:space:]]' \
		|| ko "library is not created with ar"

	if ! make -C "$BUILD" > "$TR/make.txt" 2>&1 || [ ! -f "$BUILD/libft.a" ]; then
		ko "make failed or libft.a not at the root" make.txt
		BUILT=2
		return
	fi
	rm -f "$TR/make.txt"
	ok "make creates libft.a"
	if make -C "$BUILD" -q 2> /dev/null \
		&& ! make -C "$BUILD" 2>&1 | grep -qE '(^|[[:space:]])(ar|cc)[[:space:]]'; then
		ok "no relink"
	else
		ko "relink (second make does something)"
	fi
	touch "$BUILD/libft.h"
	make -C "$BUILD" -q 2> /dev/null && warn "objects do not depend on libft.h"
	make -C "$BUILD" > /dev/null 2>&1
	make -C "$BUILD" clean > /dev/null 2>&1
	if [ -z "$(find "$BUILD" -name '*.o')" ] && [ -f "$BUILD/libft.a" ]; then
		ok "clean removes objects only"
	else
		ko "clean must remove every .o and keep libft.a"
	fi
	make -C "$BUILD" > /dev/null 2>&1
	make -C "$BUILD" fclean > /dev/null 2>&1
	if [ -z "$(find "$BUILD" -name '*.o' -o -name '*.a')" ]; then
		ok "fclean removes objects and libft.a"
	else
		ko "fclean leaves .o or .a files"
	fi
	make -C "$BUILD" fclean > /dev/null 2>&1
	make -C "$BUILD" libft.a > /dev/null 2>&1 && [ -f "$BUILD/libft.a" ] \
		&& ok "make libft.a works" || ko "make libft.a (the NAME rule) failed"
	if make -C "$BUILD" re > /dev/null 2>&1 && [ -f "$BUILD/libft.a" ]; then
		ok "re rebuilds"
		BUILT=1
	else
		ko "re failed"
		BUILT=2
	fi
}

check_protos()
{
	section prototypes
	build || return
	grep -qE '^#[[:space:]]*ifndef' "$BUILD/libft.h" && grep -qE '^#[[:space:]]*define' "$BUILD/libft.h" \
		&& ok "include guard" || ko "libft.h has no include guard"
	grep -qw restrict "$BUILD"/*.c "$BUILD"/*.h && ko "restrict is forbidden"
	if cc -Wall -Wextra -Werror -c "$ROOT/utils/protos.c" -I "$BUILD" \
		-o "$BUILD/protos.o" 2> "$TR/protos.txt"; then
		ok "t_list and the $(echo $ALL | wc -w) prototypes match the subject"
		rm -f "$TR/protos.txt"
	else
		ko "prototypes or t_list differ from the subject" protos.txt
		grep -E 'error|note: expected' "$TR/protos.txt" | head -8 | sed 's/^/        /'
	fi
}

check_symbols()
{
	section symbols
	build || return
	local objs=$BUILD/.objs f s und bad=0
	rm -rf "$objs" && mkdir "$objs" && (cd "$objs" && ar x ../libft.a)
	for f in $ALL; do
		[ -f "$objs/$f.o" ] || { ko "$f is not in libft.a"; bad=1; continue; }
		und=$(nm -u "$objs/$f.o" | awk '{ print $NF }' \
			| grep -vE '^(ft_.*|__stack_chk_fail|_GLOBAL_OFFSET_TABLE_)$')
		for s in $und; do
			[[ " ${ALLOWED[$f]} " == *" $s "* ]] && continue
			ko "$f uses forbidden function $s"; bad=1
		done
	done
	[ $bad = 0 ] && ok "no forbidden functions"
	bad=0
	while read -r _ type s; do
		case $type in
			T) is_func "$s" && continue
				if [ "$s" = main ]; then ko "main inside libft.a"; bad=1
				elif [[ "$s" == ft_* ]]; then warn "extra function $s"
				else ko "helper $s is not static"; bad=1; fi ;;
			B|D|C|G|S|R) ko "global variable $s"; bad=1 ;;
		esac
	done < <(nm -g --defined-only "$BUILD/libft.a" | awk 'NF == 3')
	while read -r _ type s; do
		[[ "$type" == [bdr] && "$s" != *.* ]] \
			&& { ko "static global variable $s"; bad=1; }
	done < <(nm --defined-only "$BUILD/libft.a" | awk 'NF == 3')
	[ $bad = 0 ] && ok "no globals and helpers are static"
}

check_readme()
{
	section readme
	local f=$LIBFT/README.md s n
	[ -f "$f" ] || { ko "README.md missing"; return; }
	head -1 "$f" | grep -qE "$README_LINE" && ok "first line" \
		|| ko "first line must be italic: This project has been created as part of the 42 curriculum by <login>"
	for s in $README_SECTIONS; do
		grep -qiE "^#+.*$s" "$f" && ok "section $s" || ko "section $s missing"
	done
	grep -qE '(^|[^A-Za-z])(AI|IA)([^A-Za-z]|$)' "$f" && ok "AI usage described" \
		|| ko "no description of how AI was used"
	n=0
	for s in $ALL; do grep -qw "$s" "$f" && n=$((n + 1)); done
	[ $n = "$(echo $ALL | wc -w)" ] && ok "library described (every function is mentioned)" \
		|| warn "detailed description of the library: only $n of $(echo $ALL | wc -w) functions mentioned"
}

run_func()
{
	local f=$1 rc mem="" lib loc="" vgw=""
	printf "  %-16s" "$f"
	[ -f "$ROOT/tests/$f.c" ] || { printf "${Y}no test file${D}\n"; return; }
	F_RUN=$((F_RUN + 1))
	lib=$BUILD
	[ $WHERE = 1 ] && lib=$BUILD/.where
	if ! cc -g -w "$ROOT/tests/$f.c" "$ROOT/utils/check.c" -I "$BUILD" \
		-I "$ROOT/utils" -L "$lib" -lft -ldl -Wl,--wrap=malloc -o "$BIN/$f" \
		2> "$TR/$f.txt"; then
		printf "${R}does not compile${D}  (traces/$f.txt)\n"
		FAILS+=("$f: does not compile or is missing")
		return
	fi
	if [ $VALGRIND = 1 ]; then
		[ $WHERE = 1 ] && vgw=--fullpath-after=
		timeout 20 valgrind -q --leak-check=full --show-leak-kinds=all $vgw \
			--errors-for-leak-kinds=all --log-file="$TR/$f.vg" "$BIN/$f" 2> "$TR/$f.txt"
		rc=$?
		[ -s "$TR/$f.vg" ] && mem=1
	else
		timeout 10 "$BIN/$f" 2> "$TR/$f.txt"
		rc=$?
	fi
	explain "$ROOT/tests/$f.c" "$TR/$f.txt"
	[ $rc = 124 ] && printf "${R}TIMEOUT${D}" && echo "TIMEOUT infinite loop?" >> "$TR/$f.txt"
	if [ $WHERE = 1 ] && { [ $rc != 0 ] || [ -s "$TR/$f.vg" ]; }; then
		where_in_code "$BIN/$f" "$TR/$f.txt" "$TR/$f.vg" > "$TR/$f.where"
		loc=$(sed -n 's/^   \([^ ]*:[0-9]*\) .*/\1/p' "$TR/$f.where" | head -1)
		cat "$TR/$f.where" >> "$TR/$f.txt"
		rm -f "$TR/$f.where"
	fi
	if [ -n "$mem" ]; then
		printf " ${R}MEM KO${D}"
		{ echo; echo "valgrind:"; cat "$TR/$f.vg"; } >> "$TR/$f.txt"
	elif [ $VALGRIND = 1 ] && [ $rc -lt 124 ]; then
		printf " ${G}MEM OK${D}"
	fi
	rm -f "$TR/$f.vg"
	if [ $rc != 0 ] || [ -n "$mem" ]; then
		printf "  (traces/$f.txt)"
		[ -n "$loc" ] && printf "  ${O}%s${D}" "$loc"
		printf "\n"
		FAILS+=("$f$(failed_tests "$TR/$f.txt")")
	else
		printf "\n"
		rm -f "$TR/$f.txt"
		F_OK=$((F_OK + 1))
	fi
}

# where mode: libft built again from the same files with -g -O0, so a crash
# or a valgrind error can be turned into file:line of the student code
build_where()
{
	local d=$BUILD/.where o
	[ -f "$d/libft.a" ] && return 0
	rm -rf "$d" && mkdir -p "$d"
	for o in $(ar t "$BUILD/libft.a" | grep '\.o$'); do
		[ -f "$BUILD/${o%.o}.c" ] || continue
		cc -g -O0 -w -c "$BUILD/${o%.o}.c" -I "$BUILD" -o "$d/$o" \
			2>> "$TR/where.txt" || { warn "where: ${o%.o}.c does not compile"; return 1; }
	done
	rm -f "$TR/where.txt"
	ar rcs "$d/libft.a" "$d"/*.o
}

# where mode: the lines of the libft found in the crash stack (frame lines
# written by check.c) and in the valgrind report, with the code of each line
where_in_code()
{
	local bin=$1 tr=$2 vg=$3 locs l file n
	locs=$( {
		sed -n 's/^   frame \([0-9a-f]*\)$/0x\1/p' "$tr" | xargs -r addr2line -e "$bin" 2> /dev/null
		[ -s "$vg" ] && grep -oE '\(/[^()]+:[0-9]+\)' "$vg" | tr -d '()'
	} | sed 's/ (discriminator.*//' | grep -F "$BUILD/" | awk '!seen[$0]++' | head -8)
	sed -i '/^   frame [0-9a-f]*$/d' "$tr"
	[ -s "$tr" ] && echo
	if [ -z "$locs" ] && ! grep -q '^CRASH' "$tr" && [ ! -s "$vg" ]; then
		echo "where in your code: a wrong result has no line, nothing crashed"
		echo "   use the why, got and expected above to find it"
		return
	elif [ -z "$locs" ]; then
		echo "where in your code: not found (the error is outside the libft code)"
		return
	fi
	echo "where in your code (first line is where it happened, the rest called it):"
	for l in $locs; do
		file=${l%:*} n=${l##*:}
		printf "   %-20s %s\n" "$(basename "$file"):$n" \
			"$(sed -n "${n}p" "$file" | sed 's/^[[:space:]]*//')"
	done
}

# after every KO or CRASH line of a trace adds the // comments written above
# that test (why) and the test itself (code), taken from tests/ft_name.c
explain()
{
	[ -s "$2" ] || return
	awk -v src="$1" '
		BEGIN { while ((getline l < src) > 0) s[++n] = l }
		{ print }
		/^(KO|CRASH)/ && match($0, /\(line [0-9]+\)/) {
			L = substr($0, RSTART + 6, RLENGTH - 7) + 0
			if (L < 1 || L > n) next
			for (i = L - 1; i > 0 && s[i] ~ /^[ \t]*\/\//; i--) ;
			for (j = i + 1; j < L; j++) {
				t = s[j]; sub(/^[ \t]*\/\/ ?/, "", t)
				print "   why   " t
			}
			for (j = L; j <= n && j < L + 4; j++) {
				t = s[j]; gsub(/^[ \t]+/, "", t)
				print (j == L ? "   code  " : "         ") t
				if (s[j] ~ /;[ \t]*$/) break
			}
		}' "$2" > "$2.tmp" && mv "$2.tmp" "$2"
}

# ": test 3 7" from a trace, empty when no test number is there
failed_tests()
{
	local n
	n=$(sed -nE 's/^(KO|CRASH).* test ([0-9]+).*/\2/p' "$1" | sort -nu \
		| head -12 | tr '\n' ' ')
	[ -n "$n" ] && printf ": test %s" "${n% }"
}

# absolute path of a libft folder into LIBFT, 1 if it is not a folder
set_libft()
{
	local d=${1/#\~/$HOME}
	[ -n "$d" ] || return 1
	[[ "$d" = /* ]] || [ -d "$d" ] || d=$ROOT/$d
	d=$(cd "$d" 2> /dev/null && pwd) || return 1
	LIBFT=$d
}

# -p, then the remembered folder, config.sh, around the tester, here
find_libft()
{
	local conf=$LIBFT d
	LIBFT=
	if [ -n "$ARG_PATH" ]; then set_libft "$ARG_PATH"; return; fi
	set_libft "$(cat "$SAVED" 2> /dev/null)" && return
	set_libft "$conf" && return
	for d in "$ROOT/.." "$PWD"; do
		[ -f "$d/libft.h" ] && set_libft "$d" && return
	done
	return 1
}

ask_path()
{
	local d
	read -e -r -p "  libft folder: " d || return
	[ -n "$d" ] || return
	if set_libft "$d"; then
		echo "$LIBFT" > "$SAVED"
		printf "  ${W}libft${D}  %s  ${M}(remembered)${D}\n" "${LIBFT/#$HOME/\~}"
		[ -f "$LIBFT/libft.h" ] \
			|| printf "  ${Y}there is no libft.h in that folder${D}\n"
	else
		printf "  ${Y}not a folder: %s${D}\n" "$d"
	fi
}

toggle_where()
{
	if [ $WHERE = 1 ]; then
		WHERE=0
		printf "  where off: only OK or KO, find the bug yourself\n"
	else
		WHERE=1
		printf "  where on: crashes and memory errors show the line of your code\n"
		printf "  ${M}a wrong result has no line: read the why and the got/expected${D}\n"
		command -v valgrind > /dev/null \
			|| printf "  ${M}valgrind is not installed, only crashes get a line${D}\n"
	fi
}

toggle_valgrind()
{
	if ! command -v valgrind > /dev/null; then
		printf "  ${Y}valgrind is not installed${D}\n"
	elif [ $VALGRIND = 1 ]; then
		VALGRIND=0
		printf "  valgrind off: faster, leaks are not checked\n"
	else
		VALGRIND=1
		printf "  valgrind on\n"
	fi
}

menu()
{
	local vg=on wh=off lib=${LIBFT/#$HOME/\~}
	[ $WHERE = 1 ] && wh=on
	[ $VALGRIND = 1 ] || vg=off
	[ -n "$lib" ] || lib="${Y}not found, press p${D}"
	printf "\n${B}== menu ==${D}\n"
	printf "  ${M}libft${D}     %s\n" "$lib"
	printf "  ${M}valgrind${D}  %s\n" "$vg"
	printf "  ${M}where${D}     %s\n" "$wh"
	[ -s "$UPD" ] && printf "  ${M}update${D}    ${O}new version available, press u${D}\n"
	printf "\n"
	printf "  ${W}1${D}  soft      function tests without valgrind (fast)\n"
	printf "  ${W}2${D}  moderate  norm, Makefile and function tests with valgrind\n"
	printf "  ${W}3${D}  strict    everything, warnings count as KO\n"
	printf "  ${W}4${D}  checks    every check, no function tests\n"
	printf "  ${W}p${D}  path      change the libft folder\n"
	printf "  ${W}v${D}  valgrind  turn it on or off\n"
	printf "  ${W}w${D}  where     show the line of your code that crashes or leaks\n"
	printf "  ${W}h${D}  help      every target and option explained\n"
	[ -s "$UPD" ] && printf "  ${W}u${D}  update    download the new version of the tester\n"
	printf "  ${W}c${D}  clean     ${W}q${D}  quit\n"
	printf "  ${M}or type any targets, like: norm split atoi${D}\n"
	printf "  ${M}your libft is copied again on every run:${D}\n"
	printf "  ${M}edit it in another tab, come back and run again${D}\n"
}

# the menu stays open until q
interactive()
{
	local pick full=1
	while :; do
		if [ $full = 1 ]; then
			menu
		else
			printf "\n  ${M}1 soft  2 moderate  3 strict  4 checks  p path  w where"
			printf "  h help  q quit  (Enter: full menu)${D}\n"
			[ -s "$UPD" ] && printf "  ${O}u update: new version of the tester${D}\n"
		fi
		full=0
		printf "\n"
		read -e -r -p "  > " pick || { printf "\n"; break; }
		[ -n "$pick" ] && history -s "$pick"
		case $pick in
			"") full=1 ;;
			1) run_targets soft ;;
			2) run_targets moderate ;;
			3) run_targets strict ;;
			4) run_targets checks ;;
			p|path) ask_path ;;
			v|valgrind) toggle_valgrind ;;
			w|where) toggle_where ;;
			u|update) update && exec "$ROOT/run.sh" "${ARGS[@]}" ;;
			h|help|-h) printf "\n"; usage ;;
			c|clean) clean ;;
			q|quit|exit) break ;;
			*) run_targets $pick ;;
		esac
	done
	printf "  bye\n"
}

# out of 100: functions weigh 70 and checks 30 when both were run
score()
{
	local c=$((CHK_OK + CHK_KO)) s=100
	if [ $F_RUN -gt 0 ] && [ $c -gt 0 ]; then
		s=$((70 * F_OK / F_RUN + 30 * CHK_OK / c))
	elif [ $F_RUN -gt 0 ]; then
		s=$((100 * F_OK / F_RUN))
	elif [ $c -gt 0 ]; then
		s=$((100 * CHK_OK / c))
	fi
	[ ${#FAILS[@]} -gt 0 ] && [ $s -gt 99 ] && s=99
	echo $s
}

bar()
{
	local n=$(($1 / 5)) i out=""
	for ((i = 0; i < 20; i++)); do
		[ $i -lt $n ] && out="$out${O}█" || out="$out${D}${M}░"
	done
	printf "%s${D}" "$out"
}

run_funcs()
{
	local f
	[ "$SECTION" = functions ] || section functions
	build || return
	if [ $WHERE = 1 ]; then build_where || return; fi
	for f in "$@"; do run_func "$f"; done
}

# git with no password prompt and a short timeout, for the update check
quiet_git()
{
	GIT_TERMINAL_PROMPT=0 GIT_SSH_COMMAND="ssh -o BatchMode=yes -o ConnectTimeout=5" \
		timeout 10 git -C "$ROOT" "$@" 2> /dev/null
}

# looks at GitHub without changing anything: .update holds the new commit
# when the remote has one that this clone does not have yet
check_update()
{
	local remote
	[ "$UPDATE_CHECK" = 1 ] || return
	git -C "$ROOT" rev-parse --git-dir > /dev/null 2>&1 || return
	remote=$(quiet_git ls-remote origin HEAD | cut -f1)
	[ -n "$remote" ] || return
	if git -C "$ROOT" merge-base --is-ancestor "$remote" HEAD 2> /dev/null; then
		rm -f "$UPD"
	else
		echo "$remote" > "$UPD"
	fi
}

# git pull of the tester: 0 updated, 1 error, 2 already up to date
update()
{
	local old new
	if ! git -C "$ROOT" rev-parse --git-dir > /dev/null 2>&1; then
		echo "  update needs a git clone of the tester:"
		echo "  git clone https://github.com/fe4d1/WankaLIB.git"
		return 1
	fi
	old=$(git -C "$ROOT" rev-parse HEAD)
	echo "  downloading the last version..."
	if ! GIT_TERMINAL_PROMPT=0 git -C "$ROOT" pull -q --ff-only --autostash; then
		printf "  ${Y}update failed${D}: no internet, or the tester has commits of\n"
		printf "  its own. ./run.sh reset puts it back as in its last commit\n"
		return 1
	fi
	rm -f "$UPD"
	new=$(git -C "$ROOT" rev-parse HEAD)
	if [ "$old" = "$new" ]; then
		echo "  already up to date"
		return 2
	fi
	printf "  ${G}updated${D}, what changed:\n"
	git -C "$ROOT" log --format='    %s' "$old..$new" | head -20
	return 0
}

clean()
{
	rm -rf "$BUILD" "$BIN" "$TR"
	echo "removed .build .bin traces"
}

reset()
{
	local changes
	git -C "$ROOT" rev-parse --git-dir > /dev/null 2>&1 \
		|| { echo "reset needs the tester to be a git clone"; exit 1; }
	clean
	changes=$(git -C "$ROOT" status --short)
	[ -z "$changes" ] && { echo "already as in the last commit"; exit 0; }
	echo "these changes will be lost:"
	echo "$changes" | sed 's/^/  /'
	printf "type yes to continue: "
	read -r answer
	[ "$answer" = yes ] || { echo "nothing done"; exit 1; }
	git -C "$ROOT" checkout -- . && git -C "$ROOT" clean -fdq \
		&& echo "tester reset to the last commit"
}

# runs the targets once and prints the result, 1 if there is a KO
run_targets()
{
	local t c f v S
	if [ -z "$LIBFT" ]; then
		printf "  ${Y}no libft folder yet: press p and type where it is${D}\n"
		return 1
	fi
	FAILS=() WARNS=0 BUILT=0 STRICT=0 SECTION=
	CHK_OK=0 CHK_KO=0 F_RUN=0 F_OK=0 SECONDS=0
	SELF=
	[ "$ROOT/.." -ef "$LIBFT" ] && SELF=${ROOT##*/}
	rm -rf "$TR" && mkdir -p "$TR"
	printf "\n  ${M}%s${D}\n" "$(say "${HELLO[@]}")"
	export T_COLS=$(tput cols 2> /dev/null || echo 80)
	export T_WHERE=$WHERE

	for t in "$@"; do
		case $t in
			soft) v=$VALGRIND; VALGRIND=0; run_funcs $ALL; VALGRIND=$v ;;
			moderate) check_norm; check_make; run_funcs $ALL ;;
			strict) STRICT=1; for c in $CHECKS; do check_$c; done; run_funcs $ALL ;;
			all) for c in $CHECKS; do check_$c; done; run_funcs $ALL ;;
			checks) for c in $CHECKS; do check_$c; done ;;
			files|header|norm|make|protos|symbols|readme) check_$t ;;
			funcs) run_funcs $ALL ;;
			part1) run_funcs $PART1 ;;
			part2) run_funcs $PART2 ;;
			part3) run_funcs $PART3 ;;
			*) f=ft_${t#ft_}
				if is_func "$f"; then run_funcs "$f"
				else echo "unknown target $t (h or -h for help)"; fi ;;
		esac
	done

	printf "\n${B}== result ==${D}\n"
	if [ $((F_RUN + CHK_OK + CHK_KO + WARNS)) = 0 ]; then
		printf "  nothing was run\n"
		rmdir "$TR" 2> /dev/null
		return 1
	fi
	S=$(score)
	printf "  ${O}score${D}      %s  ${O}%d / 100${D}\n" "$(bar $S)" $S
	printf "  ${O}           only a guide: at 42 one KO means 0${D}\n"
	[ $F_RUN -gt 0 ] && printf "  functions  %d / %d\n" $F_OK $F_RUN
	[ $((CHK_OK + CHK_KO)) -gt 0 ] \
		&& printf "  checks     %d / %d\n" $CHK_OK $((CHK_OK + CHK_KO))
	[ $WARNS -gt 0 ] && printf "  ${Y}warnings   %d${D}\n" $WARNS
	printf "  time       %ds\n" $SECONDS
	if [ ${#FAILS[@]} = 0 ]; then
		printf "\n  ${C} CONGRATZ MY G-DOGO, U GOOD TO GO NOW B) ${D}\n"
		printf "  ${M}%s${D}\n" "$(say "${WIN[@]}")"
		rmdir "$TR" 2> /dev/null
		return 0
	fi
	if [ $S -lt 30 ]; then v="WE GOTTA DO SMTHH ABT THIS"
	elif [ $S -lt 70 ]; then v="AIGHT NOW WE TALKINGG"
	else v="ALMOST THEAAA DOGG CHECK IT OUTT"; fi
	printf "\n  ${O}%s${D}\n" "$v"
	printf "\n  ${R} %d KO ${D}  ${B}at 42 this run would be a 0${D}\n" ${#FAILS[@]}
	printf '    %s\n' "${FAILS[@]}"
	printf "  traces in %s\n" "${TR/#$HOME/\~}"
	printf "  ${M}%s${D}\n" "$(say "${LOSE[@]}")"
	return 1
}

case $1 in
	clean) clean; exit 0 ;;
	update) update; [ $? != 1 ]; exit $? ;;
	reset) reset; exit $? ;;
esac

while getopts "p:u:nwh" opt; do
	case $opt in
		p) ARG_PATH=$OPTARG ;;
		u) LOGIN=$OPTARG ;;
		n) VALGRIND=0 ;;
		w) WHERE=1 ;;
		h) usage; exit 0 ;;
		*) usage; exit 1 ;;
	esac
done
shift $((OPTIND - 1))

command -v valgrind > /dev/null || VALGRIND=0
find_libft
if [ -n "$ARG_PATH" ] && [ -z "$LIBFT" ]; then
	echo "libft folder not found: $ARG_PATH"
	exit 1
fi
banner
[ -t 1 ] && { check_update & } 2> /dev/null
[ -s "$UPD" ] && printf "  ${O}new version of the tester: press u in the menu or ./run.sh update${D}\n"

if [ "$1" = menu ] || { [ $# = 0 ] && [ -t 0 ] && [ -t 1 ]; }; then
	interactive
	exit 0
fi
if [ -z "$LIBFT" ]; then
	echo "libft folder not found (use -p path, or run ./run.sh alone and press p)"
	exit 1
fi
printf "  ${M}%s${D}\n" "${LIBFT/#$HOME/\~}"
[ $# = 0 ] && set -- all
run_targets "$@"
exit $?
