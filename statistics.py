from collections import Counter


class StatisticsCalculator:
    """Calculate mean, median, and all mode values for a non-empty integer list."""

    def __init__(self, values):
        if not values:
            raise ValueError("values must not be empty")
        self.values = list(values)

    def mean(self):
        return sum(self.values) / len(self.values)

    def median(self):
        ordered = sorted(self.values)
        middle = len(ordered) // 2
        if len(ordered) % 2:
            return float(ordered[middle])
        return (ordered[middle - 1] + ordered[middle]) / 2

    def mode(self):
        frequencies = Counter(self.values)
        highest = max(frequencies.values())
        return sorted(value for value, count in frequencies.items()
                      if count == highest)


if __name__ == "__main__":
    data = [4, 2, 7, 2, 9, 4, 2, 6]
    calculator = StatisticsCalculator(data)
    print(f"Values: {', '.join(map(str, data))}")
    print(f"Mean: {calculator.mean():.2f}")
    print(f"Median: {calculator.median():.2f}")
    print(f"Mode: {', '.join(map(str, calculator.mode()))}")
