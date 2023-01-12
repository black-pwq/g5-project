#!/bin/bash
root="D:/Mine/Courses/Professional Courses/Computer Graphics/G5_Project";
builddir="/"${root/:/}"/build";
if [[ ! $1 ]]; then
	echo "No arg passed into, use root directory";
	srcdir="$root";
else
	srcdir="$1";
fi

echo "srcdir=$srcdir"
echo "builddir=$builddir"

function build() {
	if [ $? ]; then 
		cmake -B "$builddir" "$srcdir";
		if [ $? ]; then
			cd "$builddir";
			cmake --build . --parallel 8;
			cd -;
		fi
	fi
}

build
# if [ -d "$builddir" ]; then
# 	echo "removing build dir";
# 	rm -rf "$builddir";
# 	build
# else
# 	build
# fi
