#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP

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

#endif // COMPONENTS_HPP