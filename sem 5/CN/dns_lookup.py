import socket

print("=== DNS Lookup Program ===")
print("1. Find IP address from Domain name")
print("2. Find Domain name from IP address")

choice = input("Enter your choice (1 or 2): ")

if choice == '1':
    domain = input("Enter domain name (e.g., www.google.com): ")
    try:
        ip = socket.gethostbyname(domain)
        print(f"IP address of {domain} is: {ip}")
    except socket.gaierror:
        print("Error: Unable to find IP address for the given domain.")
        
elif choice == '2':
    ip = input("Enter IP address (e.g., 8.8.8.8): ")
    try:
        domain = socket.gethostbyaddr(ip)
        print(f"Domain name for IP {ip} is: {domain[0]}")
    except socket.herror:
        print("Error: Unable to find domain for the given IP address.")
else:
    print("Invalid choice! Please enter 1 or 2.")
