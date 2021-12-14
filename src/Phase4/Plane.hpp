#pragma once
#include "../Vector.hpp"
#include "../Phase3/RigidBody.hpp"

using namespace std;


/// Represents a finite plane.
/// Only the axis-aligned normales are supported, ensuring bounding box
/// is appropriate and does not need special computation.
class Plane : public RigidBody {
	public: 
		/// Normal of the plane.
		enum Normale { Xm, Xp, Ym, Yp, Zm, Zp };
	private:
		Normale normale;   ///< One of the 6 axis-aligned normales.
		float   offset;    ///< Distance from origin to the plane. Center of plane is Normale*distance.
		float   size;      ///< Radius of the square used for bounding box and to render the plane.
		Vector3 color;     ///< Color used for rendering.
	public:
		Plane(Particle const& mass_center, Matrix3 inertia, float angdamping,
	          Normale normale, float offset, float size, Vector3 color)
		:
			RigidBody(mass_center, inertia, angdamping),
			normale(normale),
			offset(offset),
			size(size),
			color(color)
		{}

		Vector3 getNormale() const;
		void setNormale(Normale);
		float getOffset() const;
		void setOffset(float);

		~Plane() override {}

		/// Draw the Plane.
		void draw() const;

    	BoundingBox getBoundingBox() const override;

    	std::vector<Vector3> getPoints() const override { return {}; }

};