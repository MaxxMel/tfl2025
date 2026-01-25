import time
import random
import matplotlib.pyplot as plt

def benchmark_simple(min_len=13, max_len=30, samples=300):
    lens = []
    slow_times = []
    fast_times = []

    for n in range(min_len, max_len + 1):
        total_slow = 0
        total_fast = 0

        for _ in range(samples):
            s = "".join(random.choice("ab") for _ in range(n))

            t0 = time.perf_counter_ns()
            simple_matches(s)
            t1 = time.perf_counter_ns()
            optimized_matches(s)
            t2 = time.perf_counter_ns()

            total_slow += (t1 - t0)
            total_fast += (t2 - t1)

        lens.append(n)
        slow_times.append(total_slow / samples)
        fast_times.append(total_fast / samples)

        print(f"n={n}")

    return lens, slow_times, fast_times

def plot_simple(lens, slow, fast):
    plt.figure()

    plt.plot(lens, slow, label="slow parser")
    plt.plot(lens, fast, label="fast parser")

    plt.xlabel("Word length")
    plt.ylabel("Average time (ns)")
    plt.title("Slow vs Fast parser")
    plt.legend()
    plt.grid(True)

    plt.show()


def gen_segments(max_len):
    segs = []
    if max_len == 0:
        return segs

    x = "a"
    y = "a"

    while len(y) <= max_len:
        segs.append(y)
        x = x + "a" + x + "b"
        y = y + x

    return segs


# ---------- SLOW ----------

def go_from(pos, x, segs):
    if pos == len(x):
        return True

    for s in segs:
        l = len(s)
        if pos + l <= len(x) and x[pos:pos + l] == s:
            if go_from(pos + l, x, segs):
                return True
    return False


def simple_matches(s):
    l = len(s)
    if l < 3 or (l - 3) % 2 != 0:
        return False

    n = (l - 3) // 2
    if s[n:n + 3] != "bab":
        return False

    left = s[:n]
    right = s[n + 3:]

    if left != right:
        return False

    if left == "":
        return True

    segs = gen_segments(len(left))
    return go_from(0, left, segs)


# ---------- FAST ----------

def parse_right_to_left(x, segs):
    pos = len(x)

    while pos > 0:
        amount_b = 0
        i = pos - 1

        while i >= 0 and x[i] == 'b':
            amount_b += 1
            i -= 1

        if amount_b >= len(segs):
            return False

        seg = segs[amount_b]
        l = len(seg)

        if l > pos:
            return False

        if x[pos - l:pos] != seg:
            return False

        pos -= l

    return True


def optimized_matches(s):
    l = len(s)
    if l < 3 or (l - 3) % 2 != 0:
        return False

    n = (l - 3) // 2
    if s[n:n + 3] != "bab":
        return False

    left = s[:n]
    right = s[n + 3:]

    if left != right:
        return False

    if left == "":
        return True

    segs = gen_segments(len(left))
    return parse_right_to_left(left, segs)


# ---------- TEST ----------

def gen_all(n, cur, out):
    if len(cur) == n:
        out.append("".join(cur))
        return
    cur.append('a')
    gen_all(n, cur, out)
    cur.pop()
    cur.append('b')
    gen_all(n, cur, out)
    cur.pop()


def main():
    MIN_LEN = 13
    MAX_LEN = 20   

    for l in range(MIN_LEN, MAX_LEN + 1):
        all_words = []
        gen_all(l, [], all_words)

        for s in all_words:
            a = simple_matches(s)
            b = optimized_matches(s)
            if a != b:
                print("MISMATCH:", s, a, b)
                return

    print("OK: parsers are equivalent")


if __name__ == "__main__":
    main()

    lens, slow, fast = benchmark_simple(
    min_len=13,
    max_len=30,
    samples=300
    )

    plot_simple(lens, slow, fast)
