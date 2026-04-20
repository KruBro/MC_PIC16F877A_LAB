# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-10/out/AS-10/default.cmf"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-10/out/AS-10/default.hex"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-10/out/AS-10/default.hxl"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-10/out/AS-10/default.mum"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-10/out/AS-10/default.o"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-10/out/AS-10/default.sdb"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-10/out/AS-10/default.sym"
  )
endif()
