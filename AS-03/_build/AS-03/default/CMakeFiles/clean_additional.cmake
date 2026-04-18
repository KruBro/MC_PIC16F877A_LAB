# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/default.cmf"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/default.hex"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/default.hxl"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/default.mum"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/default.o"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/default.sdb"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/default.sym"
  )
endif()
