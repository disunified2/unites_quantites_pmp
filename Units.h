#ifndef UNITS_H
#define UNITS_H

#include <cstdint>
#include <ratio>

namespace phy {

  /*
   * A unit defined in terms of the base units
   */
  template<int Metre, int Kilogram, int Second, int Ampere, int Kelvin, int Mole, int Candela>
  struct Unit {
    static constexpr int metre = Metre;
    static constexpr int kilogram = Kilogram;
    static constexpr int second = Second;
    static constexpr int ampere = Ampere;
    static constexpr int kelvin = Kelvin;
    static constexpr int mole = Mole;
    static constexpr int candela = Candela;
  };

  /*
   * Various type aliases
   */

  using Metre               = Unit<1, 0, 0, 0, 0, 0, 0>;
  using Kilogram            = Unit<0, 1, 0, 0, 0, 0, 0>;
  using Second              = Unit<0, 0, 1, 0, 0, 0, 0>;
  using Ampere              = Unit<0, 0, 0, 1, 0, 0, 0>;
  using Kelvin              = Unit<0, 0, 0, 0, 1, 0, 0>;
  using Mole                = Unit<0, 0, 0, 0, 0, 1, 0>;
  using Candela             = Unit<0, 0, 0, 0, 0, 0, 1>;
  using Radian              = Unit<0, 0, 0, 0, 0, 0, 0>;

  using Volt                = Unit<2, 1, -3, -1, 0, 0, 0>;
  using Ohm                 = Unit<2, 1, -3, -2, 0, 0, 0>;
  using Watt                = Unit<2, 1, -3, 0, 0, 0, 0>;
  using Hertz               = Unit<0, 0, -1, 0, 0, 0, 0>;
  using Pascal              = Unit<-1, 1, -2, 0, 0, 0, 0>;
  using Speed               = Unit<1, 0, -1, 0, 0, 0, 0>;
  using Newton              = Unit<1, 1, -2, 0, 0, 0, 0>;

  /*
   * A quantity is a value associated with a unit and a ratio
   */
  template<class U, class R = std::ratio<1>>
  struct Qty {
    using Unit = U;
    using Ratio = R;

    intmax_t value;

      Qty() : value(0) {};
      Qty(intmax_t v) : value(v) {};

    template<typename ROther>
    Qty& operator+=(Qty<U, ROther> other) {
        using ratio = std::ratio_divide<ROther,R>;
        this->value += other.value * ratio::num / ratio::den;

        return *this;
    }

    template<typename ROther>
    Qty& operator-=(Qty<U, ROther> other) {
        using ratio = std::ratio_divide<ROther,R>;
        this->value -= other.value * ratio::num / ratio::den;

        return *this;
    }

  };

  /*
   * Various quantities
   */

  using Length                = Qty<Metre>;
  using Mass                  = Qty<Kilogram>;
  using Time                  = Qty<Second>;
  using Current               = Qty<Ampere>;
  using Temperature           = Qty<Kelvin>;
  using Amount                = Qty<Mole>;
  using LuminousIntensity     = Qty<Candela>;

  using Frequency             = Qty<Hertz>;
  using Force                 = Qty<Newton>;
  using MeterSecond           = Qty<Speed>;
  using ElectricPotential     = Qty<Volt>;
  using ElectricalResistance  = Qty<Ohm>;
  using Power                 = Qty<Watt>;
  using Pressure              = Qty<Pascal>;

  /*
   * Some weird quantities
   */

  using Mile                  = Qty<Metre, std::ratio<1609344, 1000>>;
  using Yard                  = Qty<Metre, std::ratio<9144, 10000>>;
  using Foot                  = Qty<Metre, std::ratio<3048, 10000>>;
  using Inch                  = Qty<Metre, std::ratio<254, 10000>>;
  using Knot                  = Qty<Speed, std::ratio<463, 900>>;

  /*
   * Cast function between two quantities
   */

  template<typename ResQty, typename U, typename R>
  ResQty qtyCast(Qty<U,R> val) {
      static_assert(std::is_same_v<typename ResQty::Unit, U>, "qtyCast requires identical units to convert to");

      using FromRatio = R;
      using ToRatio = typename ResQty::Ratio;

      using Conv = std::ratio_divide<FromRatio, ToRatio>;

      ResQty res;
      res.value = val.value * Conv::num / Conv::den;
      return res;
  }

  /*
   * Comparison operators
   */

  // All comparison operators are between two of the same aliases

  template<typename U, typename R1, typename R2>
  bool operator==(Qty<U, R1> q1, Qty<U, R2> q2) {
      using CommonQty = Qty<U, std::ratio<1>>;
      CommonQty val1 = qtyCast<CommonQty>(q1);
      CommonQty val2 = qtyCast<CommonQty>(q2);
      return val1.value == val2.value;      // return val1.value == val2.value;
  }

  template<typename U, typename R1, typename R2>
  bool operator!=(Qty<U, R1> q1, Qty<U, R2> q2) {
      return !(q1 == q2);
  }

  template<typename U, typename R1, typename R2>
  bool operator<(Qty<U, R1> q1, Qty<U, R2> q2) {
      using CommonQty = Qty<U, std::ratio<1>>;
      CommonQty val1 = qtyCast<CommonQty>(q1);
      CommonQty val2 = qtyCast<CommonQty>(q2);
      return val1.value < val2.value;
  }

  template<typename U, typename R1, typename R2>
  bool operator<=(Qty<U, R1> q1, Qty<U, R2> q2) {
      return q1 < q2 || q1 == q2;
  }

  template<typename U, typename R1, typename R2>
  bool operator>(Qty<U, R1> q1, Qty<U, R2> q2) {
      using CommonQty = Qty<U, std::ratio<1>>;
      CommonQty val1 = qtyCast<CommonQty>(q1);
      CommonQty val2 = qtyCast<CommonQty>(q2);
      return val1.value > val2.value;
  }

  template<typename U, typename R1, typename R2>
  bool operator>=(Qty<U, R1> q1, Qty<U, R2> q2) {
      return q1 > q2 || q1 == q2;
  }

  /*
   * Arithmetic operators
   */

  template<typename U, typename R1, typename R2>
  auto operator+(Qty<U, R1> q1, Qty<U, R2> q2);

  template<typename U, typename R1, typename R2>
  auto operator-(Qty<U, R1> q1, Qty<U, R2> q2);

#if 0
  template<typename U1, typename R1, typename U2, typename R2>
  auto operator*(Qty<U1,R1> q1, Qty<U2,R2> q2);

  template<typename U1, typename R1, typename U2, typename R2>
  auto operator/(Qty<U1, R1> q1, Qty<U2, R2> q2);
#endif

  namespace literals {

    /*
     * Some user-defined literals
     */

    inline Length operator ""_metres(unsigned long long int val);
    inline Mass operator ""_kilograms(unsigned long long int val);
    inline Time operator ""_seconds(unsigned long long int val);
    inline Current operator ""_amperes(unsigned long long int val);
    inline Temperature operator ""_kelvins(unsigned long long int val);
    inline Amount operator ""_moles(unsigned long long int val);
    inline LuminousIntensity operator ""_candelas(unsigned long long int val);
    inline Temperature operator ""_celsius(unsigned long long int val);

  }

}

#endif // UNITS_H
