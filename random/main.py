from decimal import Decimal
import decimal
import matplotlib.pyplot as plt


class Paycheck:
    def __init__(self, gross: Decimal) -> None:
        self._gross = gross

    @property
    def gross(self) -> Decimal:
        return self._gross

    @property
    def net(self) -> Decimal:
        return (
            self._gross
            - self.get_pension_I()
            - self.get_pension_II()
            - self.get_taxed_income()
        ).quantize(Decimal(4.0))

    # https://mss.gov.hr/kapitalizirana-stednja-ii-i-iii-stup/116
    def get_pension_I(self) -> Decimal:
        # 15% of gross goes to pension_I
        pension_I_percentage = Decimal(0.15)

        # If lower then 700 then the reduction is fixed and is 300
        # (gross - 300) * 0.15
        if self.gross < 700:
            return Decimal((1000 - 300) * pension_I_percentage)
        elif self.gross <= 1300:
            # If between 700 and 1300 then the reduction is calculated:
            # 0.5 * (1300 - gross)
            reduction = Decimal(0.5) * (1300 - self.gross)
            return (self.gross - reduction) * pension_I_percentage
        else:
            return self.gross * pension_I_percentage

    # https://mss.gov.hr/kapitalizirana-stednja-ii-i-iii-stup/116
    def get_pension_II(self) -> Decimal:
        pension_II_percentage = Decimal(0.05)

        return self._gross * pension_II_percentage

    # https://www.porezna-uprava.hr/baza_znanja/Stranice/OsobniOdbitak.aspx
    def get_personal_deduction(self) -> Decimal:
        # TODO get children
        return Decimal(560)

    # https://gov.hr/hr/porez-na-dohodak/1466?lang=hr
    # lower and higher vary from city to city
    def get_taxed_income(self) -> Decimal:
        above_threshold_tax = Decimal(0.3)
        below_threshold_tax = Decimal(0.2)

        taxable_amount = (
            self._gross
            - self.get_pension_I()
            - self.get_pension_II()
            - self.get_personal_deduction()
        )

        income_taxed_lower = below_threshold_tax * min(taxable_amount, 4200)
        income_taxed_higher = above_threshold_tax * max(0, taxable_amount - 4200)

        return income_taxed_lower + income_taxed_higher

    def __repr__(self) -> str:
        return f"""Paycheck{{
    gross: {self.gross}
    net: {self.net}
    taxed_income: {self.get_taxed_income()}
    pension_I: {self.get_pension_I()}
    pension_II: {self.get_pension_II()}
}}"""


def draw_plot_net_to_gross(paychecks: list[Paycheck]):
    gross = [pay.gross for pay in paychecks]
    net = [pay.net for pay in paychecks]

    figure, ax = plt.subplots()
    ax.plot(
        gross,
        net,
        linestyle="--",
        marker="o",
        color="b",
        label="Net to Gross ratio increase",
    )
    ax.plot(
        [0, 1000, 2000, 5000, 6000],
        [0, 1000, 2000, 5000, 6000],
        linestyle="--",
        marker="o",
        color="r",
        label="Normal line",
    )
    # ax.plot(gross, net, "ro")

    # set the basic properties
    ax.set_xlabel("Gross (EUR)")
    ax.set_ylabel("Net (EUR)")
    ax.set_title("Net to Gross income increase")

    ax.grid("on")
    ax.legend()


def draw_plot_taxed(paychecks: list[Paycheck]):
    gross = [pay.gross for pay in paychecks]
    taxed = [pay.gross - pay.net for pay in paychecks]

    figure, ax = plt.subplots()
    ax.plot(
        gross,
        taxed,
        linestyle="--",
        marker="o",
        color="b",
        label="Taxed",
    )
    ax.plot(
        [0, 1000, 2000, 5000, 6000],
        [0, 1000, 2000, 5000, 6000],
        linestyle="--",
        marker="o",
        color="r",
        label="Normal line",
    )
    # ax.plot(gross, net, "ro")

    # set the basic properties
    ax.set_xlabel("Gross (EUR)")
    ax.set_ylabel("Taxed (EUR)")
    ax.set_title("Tax increase with gross")

    ax.grid("on")
    ax.legend()


def main():
    decimal.getcontext().prec = 6
    paychecks = [Paycheck(Decimal(gross)) for gross in range(800, 6100, 100)]

    draw_plot_net_to_gross(paychecks)
    draw_plot_taxed(paychecks)
    plt.show()


main()
