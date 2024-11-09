#include <SDL_render.h>
#include <stdlib.h>

#include "constants.h"
#include "linked_list.h"
#include "structure.h"
#include "rendering.h"

//Mon ami obstacle
// We can create many methods like this one to define the shape of an obstacle, in this case it is a small plus
Node* add_small_plus_obstacle(Node* obstacle_head, const Position* position)
{
  NodeType data;
  data.position.x = position->x;
  data.position.y = position->y;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y--;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y++;
  data.position.x++;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y++;
  data.position.x--;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y--;
  data.position.x--;
  obstacle_head = front_insert(obstacle_head, &data);

  return obstacle_head;
}

Node* add_big_plus_obstacle(Node* obstacle_head, const Position* position)
{
  NodeType data;
  data.position.x = position->x;
  data.position.y = position->y;

  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y++;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y++;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y++;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y++;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y++;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.x++;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y--;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y--;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y--;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y--;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y--;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y += 2;
  data.position.x -= 3;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.x++;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.x++;

  data.position.x++;

  data.position.x++;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.x++;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.y++;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.x--;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.x--;

  data.position.x--;

  data.position.x--;
  obstacle_head = front_insert(obstacle_head, &data);

  data.position.x--;
  obstacle_head = front_insert(obstacle_head, &data);

  return obstacle_head;
}

void initialize_obstacles(Game* game)
{
  Node* obstacle_head = NULL;
  // here we should define the position of the small plus obstacles
  const Position small_obstacle_position[] = {{3, 3}, {22, 3}, {3, 22}, {22, 22}};
  for (int i = 0; i < sizeof(small_obstacle_position) / sizeof(Position); i++)
    obstacle_head = add_small_plus_obstacle(obstacle_head, &small_obstacle_position[i]);

  const Position big_obstacle_position[] = {{12, 14},{12, 6}};
  for (int i = 0; i < sizeof(big_obstacle_position) / sizeof(Position); i++)
    obstacle_head = add_big_plus_obstacle(obstacle_head, &big_obstacle_position[i]);
  game->obstacle_head = obstacle_head;
}

void render_obstacles(SDL_Renderer* renderer, const Node* obstacle_head)
{
  while (obstacle_head != NULL)
  {
    render_square(renderer, &obstacle_head->data.position, (Color) OBSTACLE_COLOR);
    obstacle_head = obstacle_head->next;
  }
}
