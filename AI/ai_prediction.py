import joblib
import pandas as pd
import os

def test_ai_model(beds, baths, size_in_acres, house_size, zip_code):

    # pickle files
    model_file = './data/house_model.pkl'
    zip_codes_file = './data/zip_code_averages.pkl'

    if not os.path.exists(model_file) or not os.path.exists(zip_codes_file):
        print("Missing .pkl files, make sure you ran the training script first.")
        return
    # Load the trained model (rb is read binary)
    ai_model = joblib.load(model_file)
    zip_code_averages = joblib.load(zip_codes_file)

    # If the zipcode provided for a prediction wasn't in our training data, use national average instead
    fallback_price = zip_code_averages.mean()

    # Print the algorithm that was used
    print("Model loaded successfully!")
    print(ai_model)
    new_house = pd.DataFrame({
        'beds': [beds],
        'baths': [baths],
        'size_in_acres': [size_in_acres],
        'house_size': [house_size],
        'zip_code': [zip_code]
    })
    # Map the zip code to its average price
    new_house['zip_code_encoded'] = new_house['zip_code'].map(zip_code_averages)
    # The Safety Net: If the mapping resulted in NaN, fill it with the fallback price
    new_house['zip_code_encoded'] = new_house['zip_code_encoded'].fillna(fallback_price)
    # Drop the original zip code column since the model only knows 'zip_code_encoded'
    new_house_df = new_house.drop(columns=['zip_code'])

    # Ensure columns are in the EXACT same order as the training script!
    features = ['beds', 'baths', 'size_in_acres', 'house_size', 'zip_code_encoded']
    X_new = new_house_df[features]

    # Predicting the house price based on the features above
    prediction = ai_model.predict(X_new)[0] # 0 Takes the price from the matrix

    print(f"Based on the following features:\n{beds} beds\n{baths} baths\n{size_in_acres} acres\n{house_size} sqft\nzipcode: {zip_code}\n"
          f"The predicted house price is: ${prediction}")

test_ai_model(7, 4, 4, 5000, 98001)