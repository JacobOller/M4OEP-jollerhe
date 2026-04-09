from sklearn.ensemble import HistGradientBoostingRegressor as HGBRegressor
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_absolute_error, r2_score
import pandas as pd
import joblib as jl
import os

def train_ai_model():
    # Note: Using your CSV file path, but remember you can change this to .json if you used the C++ library!
    file = './data/clean_house_data.json'

    if not (os.path.exists(file)):
        print(f"File with path: {file} not found! Run C++ Program First.")
        return

    print(f"Reading clean house data from {file} into a pandas dataframe.")
    df = pd.read_json(file)

    # 1. SEPARATE FEATURES AND TARGET FIRST
    features = ['beds', 'baths', 'size_in_acres', 'house_size', 'zip_code']
    target = 'price'

    X = df[features]
    y = df[target]

    # 2. PERFORM THE TRAIN/TEST SPLIT (80% Training, 20% Testing)
    # This prevents Data Leakage!
    print("Splitting data into training and testing sets.")
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    # 3. TARGET ENCODING (Safely on Training Data Only)
    print("Encoding zip codes safely.")
    train_data = X_train.copy()
    train_data['price'] = y_train

    # Calculate averages using ONLY training data
    zip_code_averages = train_data.groupby('zip_code')['price'].mean()

    # Map the averages back to both X_train and X_test
    X_train['zip_code_encoded'] = X_train['zip_code'].map(zip_code_averages)
    X_test['zip_code_encoded'] = X_test['zip_code'].map(zip_code_averages)

    # If a zip code ended up in the test set that wasn't in the train set, fill it with the overall average
    overall_average = y_train.mean()
    X_test['zip_code_encoded'] = X_test['zip_code_encoded'].fillna(overall_average)

    # Drop the original string zip code column
    X_train = X_train.drop(columns=['zip_code'])
    X_test = X_test.drop(columns=['zip_code'])

    # 4. TRAIN THE MODEL
    print("Now Training the Model...")
    model = HGBRegressor(max_iter=200, max_depth=5, learning_rate=.05)
    model.fit(X_train, y_train)

    # 5. EVALUATE THE MODEL (The Report Card)
    print("Evaluating Model Performance on hidden test data...")
    predictions = model.predict(X_test)

    mae = mean_absolute_error(y_test, predictions)
    r2 = r2_score(y_test, predictions)

    print("\n--- Model Report Card ---")
    print(f"Mean Absolute Error (MAE): ${mae:,.2f} (On average, the AI is off by this much)")
    print(f"R-Squared Score (R2):      {r2:.4f} (1.0 is perfect, 0.0 is guessing)")
    print("-------------------------\n")

    # 6. SAVE THE MODEL
    # We save the model AND the zip code averages so our future prediction script can use them
    jl.dump(model, './data/house_model.pkl')
    jl.dump(zip_code_averages, './data/zip_code_averages.pkl')
    print("'house_model.pkl' and 'zip_code_averages.pkl' have successfully been created")

if __name__ == "__main__":
    train_ai_model()