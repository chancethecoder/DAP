# test on linux, used python3(3.4.3)
#

from scipy import stats
import numpy as np
import json

def calc_and_print(x, y):
  slope, intercept, r_value, p_value, std_err = stats.linregress(x, y)
  pcc, p_value = stats.pearsonr(x, y)
  print("R square:", r_value**2)
  print("Pearson's r:", pcc)
  print("diff:", (pcc - r_value**2))
  print("\n")

if __name__ == "__main__":
  with open('data.json') as data_file:
    json_file = json.load(data_file)

  data = json_file['data']
  x = [d['x'] for d in data]
  y = [d['y'] for d in data]

  for i in range(10):
    upto = int(len(x)/(10 - i))
    calc_and_print(x[:upto], y[:upto])
