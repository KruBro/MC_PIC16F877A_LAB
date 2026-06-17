# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-09/out/AS-09/default.cmf"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-09/out/AS-09/default.hex"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-09/out/AS-09/default.hxl"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-09/out/AS-09/default.mum"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-09/out/AS-09/default.o"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-09/out/AS-09/default.sdb"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-09/out/AS-09/default.sym"
  )
endif()
