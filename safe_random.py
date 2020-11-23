import cRandom


def singleton(cls):
    instances = {}

    def get_instance():
        if cls not in instances:
            instances[cls] = cls()
        return instances[cls]

    return get_instance()


@singleton
class safeRandom:
    def __init__(self, new_seed=0):
        self.seed(new_seed)

    def seed(self, new_seed=0):
        self.new_seed = new_seed
        cRandom.seed(new_seed)

    def uniform(self, low=0.0, high=1.0):
        return cRandom.uniform() * (high - low) + low
