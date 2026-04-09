

Note: I utilized Google Gemini in order to figure out where to start with training an AI Model. 
Gemini referenced GradientBoostingRegressor from skykit-learn, and after researching this technique, I found that
HistGradientBoostingRegressor was better for larger datasets. I cited the source that I used to learn more about this 
AI training technique as (source 1). Gemini provided me with examples of training AI models using this technique as well as
loading my data into a pandas dataframe, which is standard for skykit-learn as it formats the data into the correct 2D matrix that is required.
Exprtoing the data as a json file using C++, as the format had to be very specific and it was giving me a lot of trouble

Things I could've done better:
    - Calculate the median house price per city instead of the mean if there exists outliers in the city (Q1 - 1.5*IQR and Q3 + 1.5*IQR).
Sources:
    (source 1): https://medium.com/data-science/gradient-boosting-regressor-explained-a-visual-guide-with-code-examples-c098d1ae425c