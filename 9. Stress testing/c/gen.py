import random, string

def get_random_string(length):
    letters = string.ascii_lowercase
    return (''.join(random.choice(letters) for _ in range(length)))

print(get_random_string(random.randint(1, 100)))