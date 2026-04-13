# Real Estate Project
## Open Ended Project 4
### Jacob Ollerhead

### General Info
An application that is built off the data of over one million house objects. This C++ based project works off of a public kaggle dataset (linked below) that includes over two million house objects, each with the following attributes:
- brokered_by -- The realtor that brokered the house
- status -- for_sale or sold
- price -- The price of the property
- bed -- the number of beds
- bath -- the number of baths (double)
- acre_lot -- the size of the property in acres
- street -- the street address encoded into an integer (I unfortunately can't decode it)
- city -- the city
- state -- the state
- zip_code -- the zip code
- house_size -- the size of the property in square feet
- prev_sold_date -- a previous sold date if it exists, otherwise empty

- I utilized Qt as my GUI choice. The reason I chose Qt over OpenGL and GLFW is because these libraries are a lot better for drawing pixels, but I from what I read Qt is a lot better for the use case that I had, which was layouts, buttons, labels, user text boxes, and just widgets in general. (source 2) was the main source that I used to get used to using widgets with Qt, along with the official documentation (source 3), although I had trouble navigating through this documentation because there were just so many different classes besides widgets that confused me. The documentation helped a lot with learning about Qt Creator, which is Qt's official application for creating UI in a simpler way that doesn't require as much code (mainly for static parts). Using Qt was a massive challenge for me, but I think that it was worth it in the end because not only did my GUI turn out the way I envisioned, but the experience also gave me a new helpful tool to work with in the future.


Note: I utilized Google Gemini for the following reasons:
- In order to figure out where to start with training an AI Model. 
    Gemini referenced GradientBoostingRegressor from skykit-learn, and after researching this technique, I found that HistGradientBoostingRegressor was better for larger datasets. I cited the source that I used to learn more about this AI training technique as (source 1). Gemini provided me with examples of training AI models using this technique as well as loading my data into a pandas dataframe, which is standard for scikit-learn as it formats the data into the correct 2D matrix that is required.
- Exporting the data as a json file using C++, as the format had to be very specific and it was giving me a lot of trouble
- I used a lot of AI for switching from CLion to vscode. The reason I wanted to make this switch was to get used to vscode, as it is a more general code editor that I will likely use extensively in the future. Vscode doesn't support C++ nearly as well as CLion, and it took me a very long time to successfully build and run my code, even with the assistance of AI. This mainly includes the json files in .vscode
- Gemini helped a lot with figuring out certain aspects of Qt, as it was something that I've never worked with before. 
- I tried to cite all the specific areas where AI helped me most, as these parts of the code (Almost entirely in the GUI, but also some in HouseManager.cpp) were causing me to struggle a lot.



Things I could've done better:
    - Calculate the median house price per city instead of the mean if there exists outliers in the city (Q1 - 1.5*IQR and Q3 + 1.5*IQR).
    - Started working on the GUI earlier, as I thought I could finish it in a smaller time frame than I actually could. This caused me to not be able to implement the ai model that I trained, which was something that I spent a good amount of time learning about and working on.
    


Sources:
    (source 1): https://medium.com/data-science/gradient-boosting-regressor-explained-a-visual-guide-with-code-examples-c098d1ae425c

    (source 2): https://www.youtube.com/watch?v=Wi9nQTDFF4U

    (source 3): https://doc.qt.io/qt-6/qtwidgets-index.html