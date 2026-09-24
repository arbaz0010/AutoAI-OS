import subprocess
import shlex

class AutonomousTaskExecutor:
    def __init__(self, ai_analysis):
        self.mode = ai_analysis.get("suggested_mode", "Standard")
        
    def parse_and_execute(self, user_prompt):
        """
        یہ فنکشن صارف کی قدرتی زبان کی ہدایت کا تجزیہ کرتا ہے 
        اور اسے محفوظ سسٹم کمانڈز میں تبدیل کر کے چلتا ہے۔
        """
        print(f"\n[AI Shell Processor] Interpreting prompt under mode: {self.mode}")
        prompt_lower = user_prompt.lower()
        
        # 1. سسٹم میٹرکس دیکھنے کی درخواست
        if "status" in prompt_lower or "check" in prompt_lower or "حالت" in prompt_lower:
            command = "uptime"
            
        # 2. میموری اور پروسیسز کی جانچ
        elif "memory" in prompt_lower or "ram" in prompt_lower or "میموری" in prompt_lower:
            command = "free -h"
            
        # 3. فائلز یا ڈائریکٹری دیکھنے کی درخواست
        elif "files" in prompt_lower or "list" in prompt_lower or "فائلیں" in prompt_lower:
            command = "ls -la"
            
        else:
            return f"[AI Engine Response] Prompt '{user_prompt}' synthesized into background routine."

        # 안전 (Safe) طریقے سے کمانڈ ایگزیکیوٹ کرنا
        try:
            result = subprocess.run(shlex.split(command), capture_output=True, text=True, check=True)
            return f"\n[AI Execution Output for '{command}']:\n{result.stdout}"
        except Exception as e:
            return f"[Execution Error] Failed to run synthesized action: {str(e)}"
