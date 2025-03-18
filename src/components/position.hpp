// julian.bottiglione@epitech.eu
#ifndef COMPONENTS_POSITION_HPP
    #define COMPONENTS_POSITION_HPP

namespace Components {

    class Position {
        public:
            Position() = default;
            Position(double x, double y)
                : _x(x), _y(y) {}
            ~Position() = default;

            inline void get(double& xOut, double& yOut) const noexcept
            {
                xOut = this->_x;
                yOut = this->_y;
            }
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
            double _x = 0;
            double _y = 0;
    };  // Position
}  // Components

#endif  // COMPONENTS_POSITION_HPP
