Brian Hong

------------------- Completed -------------------
- modified quadratic_probing.h
    - added TotalElements(), TotalCollisions(), Size(), Get()
- created linear_probing.h
    - same as quadratic_probing.h
- created double_hashing.h
    - modified FindPos()
    - otherwise same as quadratic_probing.h and linear_probing.h
- modified spell_check.cc
    - added code to MakeDictionary(...), SpellChecker(...)

------------------ Imcomplete/Bugs --------------
- probe count and collisions count is off on gradescope
- SpellChecker(...) fails to properly check after one incorrect word