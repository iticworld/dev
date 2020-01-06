# CREATE 2 NEW LISTS HEIGHT AND WEIGHTS
height = [1.87,  1.87, 1.82, 1.91, 1.90, 1.85]
weight = [81.65, 97.52, 95.25, 92.98, 86.18, 88.45]

# IMPORT THE NUMPY PACKAGE AS NP
import numpy as np

# CREATE 2 NUMPY ARRAYS FROM HEIGHT AND WEIGHT
np_height = np.array(height)
np_weight = np.array(weight)

print(type(np_height))

bmi = np_weight / np_height ** 2

# PRINT THE RESULT
print(bmi)

# FOR A BOOLEAN RESPONSE
bmi > 23

# PRINT ONLY THOSE OBSERVATION ABOVE 23
bmi[bmi > 23]

weight_kg = [81.65, 97.52, 95.25, 92.98, 86.18, 88.45]

import numpy as np

# CREATE A NUMPY ARRAY NP_WEIGHT_KG FROM WEIGHT_KG
np_weight_kg = np.array(weight_kg)

# CREATE NP_WEIGHT_LBS FROM NP_WEIGHT_KG
np_weight_lbs = np_weight_kg * 2.2

# PRINT OUT NP_WEIGHT_LBS
print(np_weight_lbs)
