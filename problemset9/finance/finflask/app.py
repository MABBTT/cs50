import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session.get("user_id")
    availablecash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
    positions = db.execute("SELECT * FROM holdings WHERE user_id = ?", user_id)
    total_stock_value = 0
    for row in positions:
        row["price"] = lookup(row["position"])["price"]
        row["value"] = row["shares"] * row["price"]
        total_stock_value += row["value"]
    grandtotal = total_stock_value + availablecash
    return render_template("index.html", positions=positions, grandtotal=grandtotal, availablecash=availablecash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        user_id = session.get("user_id")

        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        symbol = request.form.get("symbol")

        if lookup(symbol) is None:
            return apology("symbol does not exist", 400)

        price = lookup(symbol)["price"]

        if not request.form.get("shares") or not request.form.get("shares").isdigit() or int(request.form.get("shares")) < 1:
            return apology("shares must be positive integer", 400)

        shares = int(request.form.get("shares"))

        value = price * shares
        availablecash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        newbalance = availablecash - value
        date = datetime.now()

        if value > availablecash:
            return apology("insufficient funds", 400)

        db.execute("INSERT INTO ledger (user_id, symbol, shares, price, type, value, start_balance, end_balance, datetime) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)",
                   user_id, symbol, shares, price, "buy", value, availablecash, newbalance, date)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", newbalance, user_id)

        if len(db.execute("SELECT shares FROM holdings WHERE user_id = ? AND position = ?", user_id, symbol)) == 0:
            db.execute("INSERT INTO holdings (user_id, position, shares) VALUES (?, ?, ?)",
                       user_id, symbol, shares)
        else:
            current_shares = db.execute("SELECT shares FROM holdings WHERE user_id = ? AND position = ?",
                                        user_id, symbol)[0]["shares"]
            new_shares = current_shares + shares
            db.execute("UPDATE holdings SET shares = ? WHERE user_id = ? AND position = ?", new_shares, user_id, symbol)
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session.get("user_id")
    if len(db.execute("SELECT * FROM ledger WHERE user_id = ?", user_id)) == 0:
        return apology("no transaction history", 400)
    history = db.execute("SELECT * FROM ledger WHERE user_id = ?", user_id)
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")

    elif not request.form.get("symbol"):
        return apology("must provide stock symbol", 400)

    else:
        if lookup(request.form.get("symbol")) is None:
            return apology("must provide valid stock symbol", 400)
        quote = lookup(request.form.get("symbol"))
        return render_template("quoted.html", quote=quote)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()
    # Implementation
    rows2 = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)

        elif len(rows2) != 0:
            return apology("username already exists, please login", 400)

        elif not request.form.get("password"):
            return apology("must provide password", 400)

        elif not request.form.get("confirmation") or request.form.get("confirmation") != request.form.get("password"):
            return apology("must correctly reenter password", 400)
        else:
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get(
                "username"), generate_password_hash(request.form.get("confirmation")))
            return render_template("login.html")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    user_id = session.get("user_id")
    positions = db.execute("SELECT * FROM holdings WHERE user_id = ?", user_id)

    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        symbol = request.form.get("symbol")

        price = lookup(symbol)["price"]

        if not request.form.get("shares") or not request.form.get("shares").isdigit() or int(request.form.get("shares")) < 1:
            return apology("shares must be positive integer", 400)

        shares = int(request.form.get("shares"))
        current_shares = db.execute("SELECT shares FROM holdings WHERE user_id = ? AND position = ?", user_id, symbol)[0]["shares"]

        if shares > current_shares:
            return apology("insufficient shares owned", 400)

        value = price * shares
        availablecash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        newbalance = availablecash + value
        date = datetime.now()

        db.execute("INSERT INTO ledger (user_id, symbol, shares, price, type, value, start_balance, end_balance, datetime) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)",
                   user_id, symbol, shares, price, "sell", value, availablecash, newbalance, date)

        db.execute("UPDATE users SET cash = ? WHERE id = ?", newbalance, user_id)

        new_shares = current_shares - shares
        db.execute("UPDATE holdings SET shares = ? WHERE user_id = ? AND position = ?", new_shares, user_id, symbol)
        return redirect("/")

    else:
        return render_template("sell.html", positions=positions)


@app.route("/changepword", methods=["GET", "POST"])
def changepword():
    """Change Password"""
    user_id = session.get("user_id")
    rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)
    if request.method == "POST":
        if request.form.get("username") != rows[0]["username"]:
            return apology("must provide correct username or logout and login again first", 403)

        elif not check_password_hash(rows[0]["hash"], request.form.get("oldpassword")):
            return apology("incorrect or missing old password", 403)

        elif request.form.get("confirmation") != request.form.get("newpassword"):
            return apology("must correctly reenter password", 403)
        else:
            db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(request.form.get("confirmation")), user_id)
            return render_template("login.html")
    else:
        return render_template("changepword.html")
