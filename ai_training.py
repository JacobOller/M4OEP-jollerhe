from sklearn.ensemble import HistGradientBoostingRegressor as HGBRegressor
import pandas as pd
import joblib as jl
import os

def train_ai_model():
    file = './data/clean_house_data.csv'

    if not (os.path.exists(file)):
        print(f"File {file} not found! Run C++ Program First.")
        return

    print(f"Reading clean house data from {file} into a pandas dataframe...")
    df = pd.read_csv(file)

    # Calculate the average price per zip code, because the algorithm caps the amount of unique values for a specific
    # category (which is what a zip code is) to be 255, and there are many zip codes in the data.
    zip_code_averages = df.groupby('zip_code')['price'].mean()

    # Map the averages back to dataframe
    df['zip_code_encoded'] = df['zip_code'].map(zip_code_averages)

    # Drop the original zip code category column
    df = df.drop(columns=['zip_code'])

    # Features based on each house object's values
    features = ['beds', 'baths', 'size_in_acres', 'house_size']
    target = 'price'

    # X is a 2D matrix, aka the data itself
    X = df[features]
    # y is the target, aka the specific data that we are training the model based on
    y = df[target]

    print("Now Training the Model...")
    ''' 
    Call HistGradientBoostingRegressor, a function from skykit-learn.
    This function is an extension of GradientBoostingRegressor, and is preferred for larger datasets.
    It creates the model, in which we pass the data and the target.
    '''
    model = HGBRegressor(max_iter=200, max_depth=12)
    # Pass our data into the model
    model.fit(X, y)

    # At this point, the model is trained, and we write the data to a special pkl file to store
    jl.dump(model, './data/house_model.pkl')
    print("'house_model.pkl' has successfully been created")

if __name__ == "__main__":
    train_ai_model()
