/* ----------------------------
   CHILD MANAGEMENT
   ---------------------------- */

/// @brief adds multiple child nodes
/// @tparam Args variadic list of child node types
/// @param args child nodes to add
/// @return current node
template<typename... Args>
shared_ptr<MenuNode> MenuNode::AddChildren(Args... args) {
    (AddChild(args), ...);
    return shared_from_this();
}