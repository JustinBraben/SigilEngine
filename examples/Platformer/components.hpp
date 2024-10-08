#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

#include <SDL2/SDL.h>

#include <vector>

enum class terrainType {
	Brick,
	Dirt
};

enum class State {
	pause,
	play
};

enum class PlayerState {
	Idle,
	Run,
	Jump,
	Fall
};

struct PlayerMovementInput {
	bool right = false, left = false;
	bool jump = false;
};

// Used to place game objects on grid
struct GridPosition {
	int x, y;
};

// Grid size
struct GridSize {
	int w = 64, h = 64;
};

struct Position {
	int x, y;

	// Member function approach
	bool operator==(const Position& other) const {
		return (x == other.x) && (y == other.y);
	}

	// Member function approach
	bool operator!=(const Position& other) const {
		return (x != other.x) && (y != other.y);
	}

	// Add this operator for ordering
	bool operator<(const Position& other) const {
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
};

struct Velocity {
	int x, y;

	// Member function approach
	bool operator==(const Velocity& other) const {
		return (x == other.x) && (y == other.y);
	}

	// Member function approach
	bool operator!=(const Velocity& other) const {
		return (x != other.x) && (y != other.y);
	}

	// Add this operator for ordering
	bool operator<(const Velocity& other) const {
		if (x != other.x) return x < other.x;
		return y < other.y;
	}
};

struct SpriteSize {
	int w, h;

	// Member function approach
	bool operator==(const SpriteSize& other) const {
		return (w == other.w) && (h == other.h);
	}

	// Member function approach
	bool operator!=(const SpriteSize& other) const {
		return (w != other.w) && (h != other.h);
	}

	// Add this operator for ordering
	bool operator<(const SpriteSize& other) const {
		if (w != other.w) return w < other.w;
		return h < other.h;
	}
};

struct CollisionBox {
	int w, h;
	int halfW, halfH;

	// Member function approach
	bool operator==(const CollisionBox& other) const {
		return	(w == other.w) && (h == other.h) &&
				(halfW == other.halfW) && (halfH == other.halfH);
	}

	// Member function approach
	bool operator!=(const CollisionBox& other) const {
		return	(w != other.w) && (h != other.h) &&
				(halfW != other.halfW) && (halfH != other.halfH);
	}

	// Add this operator for ordering
	bool operator<(const CollisionBox& other) const {
		if (w != other.w) return w < other.w;
		return h < other.h;
	}
};

struct Text {
	const char* str;
	SDL_Color foregroundColor;
	SDL_Color backgroundColor;
};

struct Sprite {
	const char* name;
};

struct SpriteSource {
	const char* name;
	int x, y;
	int w, h;
};

struct SpriteAnimator {
	const char* name;
	// Current frame of animation
	size_t frame = 0;
	// The last frame of the animation
	size_t lastFrame = 0;
	// time elapsed since last animating
	float elapsed = 0;
	// pause or run the animation
	State state = State::pause;
	// fps the animation is expected to run at
	size_t fps = 0;
	int w = 0, h = 0;
	SDL_RendererFlip flip;
};

#endif // COMPONENTS_HPP