# CMake generated Testfile for 
# Source directory: /home/ubuntu/workspace/cmake/cmake-3.5.2
# Build directory: /home/ubuntu/workspace/cmake/cmake-3.5.2
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/ubuntu/workspace/cmake/cmake-3.5.2/Tests/EnforceConfig.cmake")
add_test(SystemInformationNew "/home/ubuntu/workspace/cmake/cmake-3.5.2/bin/cmake" "--system-information" "-G" "Unix Makefiles")
subdirs(Source/kwsys)
subdirs(Utilities/KWIML)
subdirs(Utilities/cmzlib)
subdirs(Utilities/cmcurl)
subdirs(Utilities/cmcompress)
subdirs(Utilities/cmbzip2)
subdirs(Utilities/cmliblzma)
subdirs(Utilities/cmlibarchive)
subdirs(Utilities/cmexpat)
subdirs(Utilities/cmjsoncpp)
subdirs(Source/CursesDialog/form)
subdirs(Source)
subdirs(Utilities)
subdirs(Tests)
subdirs(Auxiliary)
