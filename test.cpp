#include "main.cpp"
#include <stdlib.h>
#define CATCH_CONFIG_MAIN


TEST_CASE("Test 1: Invalid Name and UFID Format") {
AVLTree tree;

SECTION("Invalid name and UFID format") {
REQUIRE(tree.Insert("A13xa", "11082002") == "unsuccessful");
}

// Add 4 more incorrect command tests here...
// Use similar code structure to test various incorrect commands
}

TEST_CASE("Test 2: Edge Cases") {
AVLTree tree;

SECTION("Removing a node that doesn't exist") {
REQUIRE(tree.Remove("12345679") == "unsuccessful");
}

// Add 2 more edge case tests here...
// Include tests for various edge cases, such as empty tree, single node, etc.
}

TEST_CASE("Test 3: Rotations") {
AVLTree tree;

SECTION("Left-Left Rotation") {
// Test left-left rotation here...
// Include tests for all four rotation cases
}

// Add 3 more rotation case tests here...
// Include tests for left-right, right-left, and right-right rotations
}

TEST_CASE("Test 4: Deletion Cases") {
AVLTree tree;

SECTION("Deleting Node with No Children") {
REQUIRE(tree.Insert("Alice", "12345678") == "successful");

// Performing a deletion with no children
REQUIRE(tree.Remove("12345678") == "successful");

// Verify that the tree is empty
vector<string> inorderResult;
tree.InorderTraversal(tree.root, inorderResult);
REQUIRE(inorderResult.empty());
}

SECTION("Deleting Node with One Child") {
REQUIRE(tree.Insert("Alice", "12345678") == "successful");
REQUIRE(tree.Insert("Bob", "87654321") == "successful");

// Performing a deletion with one child
REQUIRE(tree.Remove("12345678") == "successful");

vector<string> inorderResult;
tree.InorderTraversal(tree.root, inorderResult);

// The tree should contain only the remaining node
vector<string> expected = {"87654321", "Bob"};
REQUIRE(inorderResult == expected);
}

SECTION("Deleting Node with Two Children") {
REQUIRE(tree.Insert("Alice", "12345678") == "successful");
REQUIRE(tree.Insert("Bob", "87654321") == "successful");
REQUIRE(tree.Insert("Charlie", "55555555") == "successful");

// Performing a deletion with two children
REQUIRE(tree.Remove("12345678") == "successful");

vector<string> inorderResult;
tree.InorderTraversal(tree.root, inorderResult);

// The tree should be balanced, and inorder traversal should be sorted
vector<string> expected = {"55555555", "87654321", "Bob", "Charlie"};
REQUIRE(inorderResult == expected);
}
}

TEST_CASE("Test 5: Insert and Remove Multiple Nodes") {
AVLTree tree;

// Insert 100 nodes
for (int i = 1; i <= 100; i++) {
string name = "Name" + to_string(i);
string ufid = to_string(10000000 + i);
REQUIRE(tree.Insert(name, ufid) == "successful");
}

// Remove 10 random nodes
for (int i = 0; i < 10; i++) {
int randomIndex = rand() % 100 + 1;
string ufidToRemove = to_string(10000000 + randomIndex);
REQUIRE(tree.Remove(ufidToRemove) == "successful");
}

// Verify the order after removal
vector<string> inorderResult;
tree.InorderTraversal(tree.root, inorderResult);
REQUIRE(inorderResult.size() == 90);

// Add more insertion and removal tests here...
}
