import requests
import sys

if len(sys.argv) == 1:
    sys.exit("Missing command-line argument")
try:
    user_input = float(sys.argv[1])
except ValueError:
    sys.exit("Command-line argument is not a number")
while True:
    try:
        r = requests.get("https://api.coindesk.com/v1/bpi/currentprice.json")
        break
    except requests.RequestException:
        continue
    
rate = float(r.json()["bpi"]["USD"]["rate_float"])

output = rate * user_input

print(f"${output:,.4f}")