# WIKI FOR ECS USAGE

## Components

Components can be any data, example:
```
struct Pos {
    int x;
    int y;
}
struct Score {
    std::size_t score;
}
```

## EntityManager

The entity manager contains and manages all components. You can create new entities and assign components to it.

```
EntityManager em;

EntityID player = em.CreateNewEntity();
Pos *playerPos = em.Assign<Pos>(player, Pos{2,3});
Score *playerScore = em.Assign<Score>(player, Score{1});
```

## EntityViewer

With the entity viewer, you can iterate over components of a specific type:

```
for (EntityID ent : EntityViewer<Pos, Score>(entityManager))
{
    Pos* playerPos = entityManager.Get<Pos>(ent);
    Score* playerScore = entityManager.Get<Score>(ent);

    // Do stuff
}
```
or all components:
```
EntityViewer<>(entityManager)
```