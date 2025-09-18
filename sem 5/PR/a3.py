# syntactic_pattern_and_char_recog.py
import numpy as np
from collections import Counter

def syntactic_pattern_ngrams(s, n=2):
    """Return sequence of n-grams and a simple token-type pattern (vowel/consonant/digit)."""
    s = s.lower()
    ngrams = [s[i:i+n] for i in range(len(s)-n+1)]
    def token_type(ch):
        if ch.isdigit(): return 'D'
        if ch in 'aeiou': return 'V'
        if ch.isalpha(): return 'C'
        return 'O'
    types = ''.join(token_type(ch) for ch in s)
    return {'ngrams': ngrams, 'types': types, 'char_counts': Counter(s)}

# Very small character templates (5x3) for 'A','B','C' as examples
TEMPLATES = {
    'A': np.array([
        [0,1,0],
        [1,0,1],
        [1,1,1],
        [1,0,1],
        [1,0,1],
    ]),
    'B': np.array([
        [1,1,0],
        [1,0,1],
        [1,1,0],
        [1,0,1],
        [1,1,0],
    ]),
    'C': np.array([
        [0,1,1],
        [1,0,0],
        [1,0,0],
        [1,0,0],
        [0,1,1],
    ]),
}

def recognize_char_bitmap(bitmap):
    """Recognize a small binary bitmap character by comparing with templates using Hamming distance."""
    best = None
    best_score = 1e9
    for label, temp in TEMPLATES.items():
        # resize if necessary (simple: only allow same shape)
        if bitmap.shape != temp.shape:
            continue
        score = np.sum(np.abs(bitmap - temp)) # Hamming-like distance
        if score < best_score:
            best_score = score
            best = label
    return best, best_score

# Simple demo
if __name__ == "__main__":
    s = "Plant123"
    pattern = syntactic_pattern_ngrams(s, n=2)
    print("String pattern ngrams:", pattern['ngrams'])
    print("Token types:", pattern['types'])
    print("Char counts:", pattern['char_counts'])

    # pretend we have a 5x3 binary bitmap for 'A' (no noise)
    bmp = TEMPLATES['A'].copy()
    label, score = recognize_char_bitmap(bmp)
    print("Recognized:", label, "score:", score)

    # with small noise
    noisy = bmp.copy()
    noisy[0,1] = 0
    label2, score2 = recognize_char_bitmap(noisy)
    print("Recognized noisy:", label2, "score:", score2)
