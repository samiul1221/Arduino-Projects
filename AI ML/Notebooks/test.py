# Full Example: Sentiment Analysis with Streamlit

# Import necessary libraries
import pandas as pd
import numpy as np
import re
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
from nltk.stem import PorterStemmer
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.feature_extraction.text import TfidfVectorizer
from keras.models import Sequential
from keras.layers import Dense
import joblib
import streamlit as st

# Load dataset (assuming IMDB dataset CSV is named "IMDB-Dataset.csv" in the same directory)
df = pd.read_csv("IMDB-Dataset.csv")

# Clean and preprocess text
df["review"] = df["review"].apply(lambda x: re.sub('<.*?>|[^\w\s]', '', x))
df["review"] = df["review"].str.lower()

# Tokenization
df["tokenized_text"] = df["review"].apply(lambda x: word_tokenize(x))

# Remove stopwords
stop_words = set(stopwords.words('english'))
df["filtered"] = df["tokenized_text"].apply(lambda x: [word for word in x if word not in stop_words])

# Stemming
stemmer = PorterStemmer()
df['stem_text'] = df["filtered"].apply(lambda x: [stemmer.stem(word) for word in x])

# Prepare X and Y
X = df['stem_text']  # Use stemmed text as input
Y = df["sentiment"]

# Train-test split
x_train, x_test, y_train, y_test = train_test_split(X, Y, test_size=0.2, random_state=42)

# Encode labels
le = LabelEncoder()
y_train = le.fit_transform(y_train)
y_test = le.transform(y_test)

# TF-IDF Vectorization
tfidf = TfidfVectorizer()
x_train = tfidf.fit_transform(x_train.apply(lambda x: ' '.join(x)))
x_test = tfidf.transform(x_test.apply(lambda x: ' '.join(x)))

# Define the model using Keras
model = Sequential([
    Dense(128, activation="relu", input_shape=(x_train.shape[1],)),
    Dense(64, activation="relu"),
    Dense(32, activation="relu"),
    Dense(1, activation="sigmoid")
])

# Compile the model
model.compile(optimizer="adam", loss="binary_crossentropy", metrics=["accuracy"])

# Train the model
model.fit(x_train, y_train, epochs=10, batch_size=32)

# Save the trained model and TF-IDF vectorizer using joblib
joblib.dump(model, 'model.pkl')
joblib.dump(tfidf, 'tfidf_vectorizer.pkl')

# Function to predict sentiment
def predict_sentiment(review):
    # Load the saved model and TF-IDF vectorizer
    model = joblib.load('model.pkl')
    tfidf = joblib.load('tfidf_vectorizer.pkl')

    # Initialize NLTK tools
    stemmer = PorterStemmer()
    stop_words = set(stopwords.words('english'))

    # Preprocess the input review
    cleaned_review = re.sub('<.*?>', '', review)
    cleaned_review = re.sub(r'[^\w\s]', '', cleaned_review)
    cleaned_review = cleaned_review.lower()
    tokenized_review = word_tokenize(cleaned_review)
    filtered_review = [word for word in tokenized_review if word not in stop_words]
    stemmed_review = [stemmer.stem(word) for word in filtered_review]
    tfidf_review = tfidf.transform([' '.join(stemmed_review)])

    # Predict sentiment
    sentiment_prediction = model.predict(tfidf_review)[0]  # Assuming model.predict returns an array

    # Return sentiment label
    if sentiment_prediction > 0.5:
        return "Positive"
    else:
        return "Negative"

# Streamlit UI
def main():
    st.title('Sentiment Analysis')
    review_to_predict = st.text_area("Enter your review here:")
    if st.button('Predict Sentiment'):
        predicted_sentiment = predict_sentiment(review_to_predict)
        st.write("Predicted Sentiment:", predicted_sentiment)

if __name__ == '__main__':
    main()
