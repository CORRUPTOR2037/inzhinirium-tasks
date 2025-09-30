from flask import Flask, render_template, jsonify, request
import logging

app = Flask(__name__, static_folder='assets', template_folder='templates')
app.config['TEMPLATES_AUTO_RELOAD'] = True

@app.route('/places')
def places():
    return render_template('places.html')

@app.route('/reviews')
def reviews():
    return render_template('reviews.html')

app.run()