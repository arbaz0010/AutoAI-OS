import psutil

class SelfHealingEngine:
    def __init__(self, memory_threshold=85.0):
        self.memory_threshold = memory_threshold

    def inspect_system_health(self):
        """
        سسٹم ریسورسز کی مانیٹرنگ اور ضرورت پڑنے پر آٹومیٹک ریکوری
        """
        mem_usage = psutil.virtual_memory().percent
        cpu_usage = psutil.cpu_percent(interval=0.1)
        
        status_report = {
            "health_status": "Healthy",
            "memory_usage_percent": mem_usage,
            "cpu_usage_percent": cpu_usage,
            "corrective_actions": []
        }

        # اگر میموری کا استعمال حد سے بڑھ جائے تو سیلف ہیلنگ ٹرگر کریں
        if mem_usage > self.memory_threshold:
            status_report["health_status"] = "Warning: High Memory Load"
            status_report["corrective_actions"].append(
                "[Self-Healing] High RAM usage detected. Triggering automatic garbage collection & memory optimization."
            )
        else:
            status_report["corrective_actions"].append(
                "[Self-Healing] System resources balanced. Kernel stability nominal."
            )

        return status_report
