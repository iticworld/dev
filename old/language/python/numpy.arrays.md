# NUMPY ARRAYS

## GETTING STARTED

Numpy arrays are great alternatives to Python Lists. Some of the key advantages of Numpy arrays are that they are fast, easy to work with, and give users the opportunity to perform calculations across entire arrays.

In the following example, you will first create two Python lists. Then, you will import the numpy package and create numpy arrays out of the newly created lists.

```
# CREATE 2 NEW LISTS HEIGHT AND WEIGHTS
height = [1.87,  1.87, 1.82, 1.91, 1.90, 1.85]
weight = [81.65, 97.52, 95.25, 92.98, 86.18, 88.45]

# IMPORT THE NUMPY PACKAGE AS NP
import numpy as np

# CREATE 2 NUMPY ARRAYS FROM HEIGHT AND WEIGHT
np_height = np.array(height)
np_weight = np.array(weight)
```

## PRINT OUT THE TYPE OF np_height

```
print(type(np_height))
```

### ELEMENT WISE CALCULATIONS

Now we can perform element-wise calculations on height and weight. For example, you could take all 6 of the height and weight observations above, and calculate the BMI for each observation with a single equation. These operations are very fast and computationally efficient. They are particularly helpful when you have 1000s of observations in your data.

```
# CALCULATE BMI
bmi = np_weight / np_height ** 2

# PRINT THE RESULT
print(bmi)
```

### SUBSETTING

Another great feature of Numpy arrays is the ability to subset. For instance, if you wanted to know which observations in out BMI array are above 23, we could quickly subset it to find out.

```
# FOR A BOOLEAN RESPONSE
bmi > 23

# PRINT ONLY THOSE OBSERVATION ABOVE 23
bmi[bim > 23]
```

## EXERCISE

First, convert the list of weights from a list to Numpy array. Then, convert all of the weights from kilograms to pounds. Use the scalar conversion of 2.2 lbs per kilogram to make your conversion. Lastly, print the resulting array of weights in pounds,

```
weight_kg = [81.65, 97.52, 95.25, 92.98, 86.18, 88.45]

import numpy as np

# CREATE A NUMPY ARRAY NP_WEIGHT_KG FROM WEIGHT_KG
np_weight_kg = np.array(weight_kg)

# CREATE NP_WEIGHT_LBS FROM NP_WEIGHT_KG
np_weight_lbs = np_weight_kg * 2.2

# PRINT OUT NP_WEIGHT_LBS
print(np_weight_lbs)
```
