from flask import Flask, render_template, jsonify


app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/refresh')
def refresh():
    

    return jsonify(data)


if __name__ == '__main__':
    app.run()
