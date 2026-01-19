# This is a basic powershell script that cleans out the build directory, and re-creates it.
# Also, this script will run the CMake build script
$confirmation = Read-Host "This deletes and re-creates the build folder, and rebuilds program with CMake press y to confirm"

# This is the path to msbuild in Visual Studio 2022, this may need to be adjusted for other Visual Studio versions.
$msbuild_path = "C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\amd64\MSBuild.exe"

# Path to the built project file.
$project_path = ".\build\KCNet-SFML-GameTest.vcxproj"

# https://stackoverflow.com/questions/24649019/how-to-use-confirm-in-powershell
if ($confirmation -eq 'y') {
	
	# Check if the build path exists, if so delete it, if not create a new one.
	# if (Test-Path -path ".\build") {
		# Remove-Item -Recurse -Force build/
		# New-Item -Path ".\build" -ItemType Directory
		# Write-Output "build folder has been removed and re-created"
	# }else{
		# New-Item -Path ".\build" -ItemType Directory
		# Write-Output "build folder has been created"
	# }
	
	# Write-Output "Switching to build folder, and running CMake."
	# cd ".\build"
	# cmake ..
	
	Write-Output "CMake build finished."
	
	# https://stackoverflow.com/questions/4677222/powershell-script-to-build-visual-studio-project
	Write-Output "Attempting to build with MSBuild, checking for MSBuild on system."
	if(Test-Path -path $msbuild_path) {
		Write-Output "Building program with MSBuild."
		& $msbuild_path $project_path
	} else {
		Write-Output "MSBuild not found, this will need to be built with Visual Studio."
	}
	
} else {
	Write-Output "Action cancelled, files were not modified."
}