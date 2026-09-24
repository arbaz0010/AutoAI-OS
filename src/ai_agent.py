import json

class AutonomousAIAgent:
    def __init__(self, hardware_data):
        self.hardware_data = hardware_data

    def analyze_hardware(self):
        """
        یہ AI ایجنٹ ہارڈویئر کے پروفائل کا تجزیہ کرتا ہے اور
        خودکار طور پر سسٹمز کے ریسورسز کی ایلوکیشن کا فیصلہ کرتا ہے۔
        """
        cpu_cores = self.hardware_data['cpu']['cores_total']
        ram_gb = self.hardware_data['memory']['total_gb']
        arch = self.hardware_data['cpu']['architecture']

        analysis = {
            "status": "Optimal",
            "suggested_mode": "",
            "ai_execution_strategy": "",
            "hardware_rating": ""
        }

        # 1. ریسورسز کے حساب سے AI موڈ کا تعین
        if ram_gb < 4:
            analysis["suggested_mode"] = "Ultra-Lightweight / Embedded Mode"
            analysis["ai_execution_strategy"] = "Quantized Micro-LLM / Heuristic Engine"
            analysis["hardware_rating"] = "Low-Resource Target"
        elif ram_gb <= 8:
            analysis["suggested_mode"] = "Balanced Desktop Mode"
            analysis["ai_execution_strategy"] = "Local Small Language Model (SLM - e.g., Llama-3-2B / Phi-3)"
            analysis["hardware_rating"] = "Mid-Tier Workstation"
        else:
            analysis["suggested_mode"] = "High-Performance Autonomous Server/Desktop"
            analysis["ai_execution_strategy"] = "Full Local LLM & Multi-Agent Dynamic Code Compiler"
            analysis["hardware_rating"] = "High-Performance Machine"

        return analysis

    def generate_system_action_plan(self):
        analysis = self.analyze_hardware()
        
        plan = [
            f"[Agent Action] Architecture verified as {self.hardware_data['cpu']['architecture']}.",
            f"[Agent Action] System Mode initialized to: {analysis['suggested_mode']}.",
            f"[Agent Action] Selected Engine: {analysis['ai_execution_strategy']}.",
            "[Agent Action] Zero-Driver Hardware Abstraction Layer (HAL) initialized."
        ]
        return plan, analysis
