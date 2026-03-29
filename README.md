Jacob Ollerhead
My program is a Real Estate Data Analyzer. I have successfully cleaned and sorted over two million House Object values from
the kaggle dataset https://www.kaggle.com/datasets/ahmedshahriarsakib/usa-real-estate-dataset. 
Each house object has the following values: BrokerId, Status, Price, # of Beds, # of Baths, Acreage, Street, City,
State, Zip Code, House Size, and Previous Sold Date. I utilized the following data values: BrokerId, Price, Beds, Baths,
Acreage, City, State, and House Size.

My program currently has a few bugs, but for the most part it is fully functional for its current intended purpose.
The bugs that my code currently doesn't account are related to my budget and city methods, where both methods will cause the program
to crash when it's finished printing all the possible values. I did not have time to fully address this issue.
I have plans to heavily expand the program, with the intent to fix these bugs as soon as possible, and 
with the ultimate goal of being able to utilize basic machine learning to do further data analysis and predictions,
and even possibly creating a UI similar to a website like Zillow. 
I am considering reaching out to the owner of the Kaggle to ask how he encoded the street addresses, since 
right now each street address is just an unusable string of numbers. If I could decode these addresses, then I could
pinpoint the location of each house and possibly even use a Google Earth dataset to link each address to a pictured home.
The only potential issue with my program and especially my data is that a lot of the house objects have dates that are 10,
20, and even 30 years old. This could definitely change the results since I am calculating the mean based off of both these
house prices and house prices from the last ~5 years.

I utilized the Heap Sorting Algorithm from CS2240 in order to sort my data. This is the only code within this project that 
was not written by me.

I believe that I have earned 85/100 of the total points, as I spent a very long time organizing my code into multiple classes
from a very large dataset. I utilized an inheritance relationship with how a DataAnalyzer object is-a HouseStatistic object.
I utilized a component relation with how a HouseManager object has-a collection of houses, and how a menu has-a HouseManager object.
I utilized file input in my HouseManager method data_from_file() in order to collect, clean, and sort the house data from a .csv file.
