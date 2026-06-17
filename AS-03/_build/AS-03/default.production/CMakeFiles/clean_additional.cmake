# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/production/default-production.cmf"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/production/default-production.hex"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/production/default-production.hxl"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/production/default-production.mum"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/production/default-production.o"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/production/default-production.sdb"
  "/home/krubro/Desktop/Emertxe/MC-Assignments/AS-03/out/AS-03/production/default-production.sym"
  )
endif()
