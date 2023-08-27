# Algorithms-and-DataStructures-SocialRelationships

## **Project Overview**

This project provides a custom data structure tailored for managing entities and their relationships within a Social Network. It prioritizes optimization of time and memory complexity using a combination of Red-Black tree data structures.

## **Features**

- Efficient addition and removal of entities and relationships.
- Combined utilization of Red-Black trees for optimal performance.

## **Structure**

1. **Entity Storage**
   - Entities are organized and maintained using a Red-Black tree.

2. **Relationship List**
   - Each entity has a list denoting the types of relationships it's involved in. The length of this list is irrelevant with respect to the complexity.

3. **Relationship Subtrees**
   - For each relationship type linked to an entity, two distinct subtrees are present. These subtrees denote:
     - Other entities that stand as the targets (destinations) of the relationship.
     - Other entities that act as the origins (sources) of the relationship.
4. **Report Structure**
   - The project features a data structure specifically tailored to generate reports on relationships among entities. This structure is incrementally updated to ensure optimal efficiency.
   
