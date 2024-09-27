import streamlit as st
import re
from nltk.tokenize import word_tokenize
from nltk.corpus import stopwords
from nltk.stem import PorterStemmer
from sklearn.feature_extraction.text import TfidfVectorizer
import joblib
import numpy

# Assuming your trained model is named 'model' and 'tfidf' is your TF-IDF vectorizer
joblib.dump(model, 'model.pkl')
joblib.dump(tfidf, 'your_tfidf_vectorizer.pkl')

# Load the model and TF-IDF vectorizer
model = joblib.load('model.pkl')
tfidf = joblib.load('your_tfidf_vectorizer.pkl')

# Initialize NLTK tools
stemmer = PorterStemmer()
stop_words = set(stopwords.words('english'))

# Function to predict sentiment
def predict_sentiment(review):
    cleaned_review = re.sub('<.*?>', '', review)
    cleaned_review = re.sub(r'[^\w\s]', '', cleaned_review)
    cleaned_review = cleaned_review.lower()
    tokenized_review = word_tokenize(cleaned_review)
    filtered_review = [word for word in tokenized_review if word not in stop_words]
    stemmed_review = [stemmer.stem(word) for word in filtered_review]
    tfidf_review = tfidf.transform([' '.join(stemmed_review)])
    sentiment_prediction = model.predict(tfidf_review)[0]  # Assuming model.predict returns an array
    if sentiment_prediction > 0.5:  # Adjust threshold as needed
        return "Positive"
    else:
        return "Negative"

# Streamlit UI
st.title('Sentiment Analysis')
review_to_predict = st.text_area("Enter your review here:")
if st.button('Predict Sentiment'):
    predicted_sentiment = predict_sentiment(review_to_predict)
    st.write("Predicted Sentiment:", predicted_sentiment)
