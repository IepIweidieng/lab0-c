# Test of sort with natural sort - Date
option fail 0
option malloc 0
option compare 4
new
ih "2000-1-10"
ih "2000-1-2"
ih "1999-12-25"
ih "2000-3-23"
ih "1999-3-3"
sort
rh "1999-3-3"
rh "1999-12-25"
rh "2000-1-2"
rh "2000-1-10"
rh "2000-3-23"
