def main():
    text = input("Enter the text: ")
    l = avgLetters(text)
    s = avgSentences(text)
    print(computeIndex(l, s))

def avgLetters(text):
    words = text.split()

    letters = []
    for word in words:
        chars = list(word)
        for char in chars:
            if char.isalpha():
                letters.append(char)
    return round(len(letters) / len(words) * 100)

def avgSentences(text):
    words = text.split()

    sentences = []
    sentences.append(text)
    splitters = [". ", "! ", "? "]

    for splitter in splitters:
        new = []
        for sentence in sentences:
            new.extend(sentence.split(splitter))
        sentences = new

    return round(len(sentences) / len(words) * 100)

def computeIndex(l, s):
    index = round(0.0588 * l - 0.296 * s - 15.8)
    return "Grade " + str(index) if index > 1 and index < 16 else "Grade 16+" if index >= 16 else "Before Grade 1"

main()
