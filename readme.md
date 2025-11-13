successfully built the Smart Shopping Cart System in C with the simplest possible implementation. Here's what I created:

Files Created:
product.h: Header with struct definitions and function declarations
product.c: Hash table implementation with chaining, product search functions
cart.h: Cart function declarations
cart.c: Cart operations (add/remove), total calculation with 15% discount over $100, colored display
main.c: Test program with sample products and operations
Key Features Implemented:
Hash Table: Simple chaining for collision handling
Product Search: By ID (O(1) average) and by name (O(n))
Cart Operations: Add/remove items, update stock automatically
Total Calculation: Sum with 15% discount for totals > $100
Display: ANSI color-coded output (blue headers, green items, yellow total)
Memory Management: Proper cleanup of all allocated memory
Test Results:
The program compiles and runs successfully, demonstrating:

Product insertion and search
Adding items to cart (including quantity updates)
Stock management during add/remove
Discount application (15% off when total > $100)
Colored console output