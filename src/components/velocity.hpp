//
#ifndef COMPONENTS_VELOCITY_HPP
    #define COMPONENTS_VELOCITY_HPP

namespace Components {

    class Velocity {
        public:
            Velocity() = default;
            Velocity(const double &&x, const double &&y)
                : _x(x), _y(y) {}
            ~Velocity() = default;
            void cap(double max)
            {
                if (this->_x  > max) {
                    this->_x = max;
                }
                if (this->_y > max) {
                    this->_y = max;
                }
            }

            Velocity& operator+(Velocity& other)
            {
                this->_x += other.getX();
                this->_y += other.getY();
                return *this;
            }
            Velocity& operator-(Velocity& other)
            {
                this->_x -= other.getX();
                this->_y -= other.getY();
                return *this;
            }
            /*Velocity& operator=(Velocity& other)
            {
                this->_x = other.getX();
                this->_y = other.getY();
                return *this;
            }*/

            double& getX() noexcept
            {
                return this->_x;
            }
            double getX() const noexcept
            {
                return this->_x;
            }
            double& getY() noexcept
            {
                return this->_y;
            }
            double getY() const noexcept
            {
                return this->_y;
            }

        private:
            double _x = 0.0;
            double _y = 0.0;
    };

}  // Components

#endif  // COMPONENTS_VELOCITY_HPP
