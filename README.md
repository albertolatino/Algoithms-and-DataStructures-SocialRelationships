# Algorithms-and-DataStructures-SocialRelationships

## **Project Overview**

This project offers a custom data structure designed for the effective management of entities and their interconnected relationships within a Social Network. By employing Red-Black tree data structures, it ensures optimized time and memory performance.

## **Features**

- Efficient addition and removal of entities and relationships.
- : Harnesses the power of Red-Black trees for top-tier efficiency.

## **Structure**

1. **Entity Storage**
   - Entities are organized and maintained using a Red-Black tree.

2. **Relationship List**
   - Each entity has a list denoting the types of relationships it's involved in. The length of this list doesn't influence the complexity.

3. **Relationship Subtrees**
   - For each relationship type linked to an entity, two distinct subtrees are present. These subtrees denote:
     - Other entities that stand as the targets (destinations) of the relationship.
     - Other entities that act as the origins (sources) of the relationship.
