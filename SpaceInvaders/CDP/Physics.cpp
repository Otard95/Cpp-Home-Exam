#include <algorithm>
#include "Headers/Physics.h"
#include "Headers/Transform.h"

using namespace CDP;

Physics::Physics()
	: m_time(Time::Instance())
	, m_rigidbodies(nullptr)
	, m_colliders(nullptr)
{}

Physics& Physics::Instance() {
	static Physics m_instance;
	return m_instance;
}

void Physics::Init(std::vector<Rigidbody> * rigidbodies,
									 std::vector<Collider> * colliders
/*std::vector<Transform> * transforms*/) {
	m_rigidbodies = rigidbodies;
	m_colliders = colliders;
	//m_transforms = std::shared_ptr<std::vector<Transform>> (transforms);

	//return m_instance;
}

void Physics::Update () {

	if (m_rigidbodies == nullptr) return;

	std::for_each(m_rigidbodies->begin(), m_rigidbodies->end(), [&](Rigidbody& rb) {


		if (!rb.m_is_kinematic) {
			if (rb.m_use_gravity)
				rb.velocity.y += 9.81 * m_time.DeltaTime();

			rb.transform.Translate(rb.velocity * m_time.DeltaTime());
		}

		std::for_each(m_colliders->begin(), m_colliders->end(), [&](Collider& col) {

			if (&rb.collider == &col) return;

			double dist = (col.transform.Position()
										 - rb.transform.Position()).Length();

			double conbinedExtent = col.extent + rb.collider.extent;

			if (dist < conbinedExtent) {
				// Do proppor collition check

				const Vector2<double>& pos1 = rb.transform.Position();
				const Vector2<double>& pos2 = col.transform.Position();
				Vector2<double> ex1 = rb.collider.bound_size / 2;
				Vector2<double> ex2 = col.bound_size / 2;
				/*left = max(r1.left, r2.left)
					right = min(r1.right, r2.right)
					bottom = min(r1.bottom, r2.bottom)
					top = max(r1.top, r2.top)*/
				double l = (pos1.x - ex1.x > pos2.x - ex2.x ? pos1.x - ex1.x : pos2.x - ex2.x);
				double r = (pos1.x + ex1.x < pos2.x + ex2.x ? pos1.x + ex1.x : pos2.x + ex2.x);
				double b = (pos1.y + ex1.y < pos2.y + ex2.y ? pos1.y + ex1.y : pos2.y + ex2.y);
				double t = (pos1.y - ex1.y > pos2.y - ex2.y ? pos1.y - ex1.y : pos2.y - ex2.y);

				// left < right && bottom < top
				if (l < r && b < t) {
					// Collition

					rb.collider.OnCollision(col);
					col.OnCollision(rb.collider);

					if (rb.collider.is_trigger) return;

					double dx = r - l;
					double dy = t - b;

					Vector2<double> rpos = pos1 - pos2;

					if (dx < dy) {
						// move in x axis
						if (rpos.x < 0)
							rb.transform.Translate(-dx, 0);
						else
							rb.transform.Translate(dx, 0);

						rb.velocity.x = 0;

					} else {
						// move in y axis
						if (rpos.y < 0)
							rb.transform.Translate(0, -dy);
						else
							rb.transform.Translate(0, dy);

						rb.velocity.y = 0;

					}

				}

			}

		});
	});

}
