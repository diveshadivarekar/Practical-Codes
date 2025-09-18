# mnist_nn.py
import numpy as np
from tensorflow.keras.datasets import mnist
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, Flatten, Conv2D, MaxPooling2D
from tensorflow.keras.utils import to_categorical
from tensorflow.keras.callbacks import EarlyStopping

def build_simple_cnn(input_shape=(28,28,1), n_classes=10):
    model = Sequential([
        Conv2D(16, kernel_size=3, activation='relu', input_shape=input_shape),
        MaxPooling2D(),
        Conv2D(32, kernel_size=3, activation='relu'),
        MaxPooling2D(),
        Flatten(),
        Dense(64, activation='relu'),
        Dense(n_classes, activation='softmax')
    ])
    model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])
    return model

if __name__ == "__main__":
    (x_train, y_train), (x_test, y_test) = mnist.load_data()
    x_train = x_train.astype('float32') / 255.0
    x_test = x_test.astype('float32') / 255.0
    # add channel dim
    x_train = x_train[..., np.newaxis]
    x_test = x_test[..., np.newaxis]
    y_train = to_categorical(y_train, 10)
    y_test_cat = to_categorical(y_test, 10)

    model = build_simple_cnn()
    print(model.summary())
    es = EarlyStopping(monitor='val_loss', patience=3, restore_best_weights=True)
    model.fit(x_train, y_train, epochs=8, batch_size=128, validation_split=0.1, callbacks=[es])
    loss, acc = model.evaluate(x_test, y_test_cat, verbose=0)
    print(f"Test accuracy: {acc:.4f}")

    # predict a single example
    import numpy as np
    idx = 0
    pred = model.predict(x_test[[idx]])
    print("True:", int(np.argmax(y_test_cat[idx])), "Predicted:", int(np.argmax(pred)))
