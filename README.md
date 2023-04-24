# cub3D
42 Cub3d project

This project is about creating a minigame using raycasting technique in C (with OpenGL MLX42 version)

The mandatory part can be compiled with `make` and has the following features:
- WASD movement keys
- `←` or `→` to rotate the camera
- you can quit by presssing `esc` or ❌

The bonus part can be compiled with `make bonus` and has the following features:
- WASD movement keys
- `←` or `→` to rotate the camera
- rotation with the mouse too
- pressing `space` will make a sound and an animation
- pressing `e` will make a sound and open a door if your cursor is on it when the sound blasts
- minimap showing walls and opened/closed doors
- you can quit by presssing `esc` or ❌

If you want to check for leaks, you can use the `make vg` or `make vg_b` make rule, which uses the leak.supp valgrind suppression file, suppressing the leaks coming from mlx_init

Here is a screenshot of the bonus part
