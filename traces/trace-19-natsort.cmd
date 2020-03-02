# Test of sort with natural sort - Fractions
option fail 0
option malloc 0
option compare 4
new
ih "Fractional release numbers"
ih "1.011.02"
ih "1.010.12"
ih "1.009.02"
ih "1.009.20"
ih "1.009.10"
ih "1.002.08"
ih "1.002.03"
ih "1.002.01"
sort
rh "1.002.01"
rh "1.002.03"
rh "1.002.08"
rh "1.009.02"
rh "1.009.10"
rh "1.009.20"
rh "1.010.12"
rh "1.011.02"
rh "Fractional release numbers"
