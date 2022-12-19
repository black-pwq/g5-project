
if(Test-Path -Path build) {
	rm -r -fo ./build
}

if($?) {
	cmake -Bbuild .
	if($?) {
		cd build
		cmake --build . --parallel 8
		cd ..
	}
} else {
	echo "---------------------------error above-------------"
}