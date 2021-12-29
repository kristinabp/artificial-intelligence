import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns


# After clustering
df = pd.read_csv("output.csv")
sns.scatterplot(x=df.x, y=df.y,
                hue=df.c,
                palette=sns.color_palette("hls", n_colors=8))
plt.xlabel("x")
plt.ylabel("y")
plt.title("First")

plt.show()