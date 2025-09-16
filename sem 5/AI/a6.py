import time

def pizza_chatbot():
    order = {
        "size": None,
        "topping": None,
        "confirmed": False
    }

    print(" Bot: Welcome to Pizza Palace! I can help you place an order.")
    time.sleep(1)

    response = input(" Bot: Would you like to start an order? (yes/no)\n> You: ").lower()
    if 'no' in response:
        print(" Bot: Okay, have a great day! 👋")
        return

    while order["size"] is None:
        response = input(" Bot: Great! What size pizza would you like? (Small, Medium, or Large)\n> You: ").lower()
        if 'small' in response:
            order["size"] = "Small"
        elif 'medium' in response:
            order["size"] = "Medium"
        elif 'large' in response:
            order["size"] = "Large"
        else:
            print(" Bot: Sorry, I didn't understand that. Please choose Small, Medium, or Large.")
            time.sleep(1)
    
    while order["topping"] is None:
        response = input(f" Bot: Got it, one {order['size']} pizza. What topping would you like? (e.g., Pepperoni, Veggie, Margherita)\n> You: ").title()
        if response:
             order["topping"] = response
        else:
            print(" Bot: Please tell me which topping you'd like.")
            time.sleep(1)

    while not order["confirmed"]:
        summary = f"one {order['size']} {order['topping']} pizza"
        response = input(f" Bot: Excellent choice! So, that's {summary}. Should I confirm your order? (yes/no)\n> You: ").lower()
        if 'yes' in response:
            order["confirmed"] = True
            print(f" Bot: Perfect! Your order for {summary} has been placed.")
            time.sleep(1)
            print(" Bot: It will be ready in 20 minutes. Thanks for ordering from Pizza Palace! 👋")
        elif 'no' in response:
            print(" Bot: Order cancelled. Let me know if you want to start over.")
            return
        else:
            print(" Bot: Sorry, I didn't catch that. Please confirm with 'yes' or 'no'.")
            time.sleep(1)


if __name__ == "__main__":
    pizza_chatbot()