module Builders
  class Vagrant < Builder
    TYPE = 'vagrant'

    def rebind(scroll_name)
      Vagrant.new(@scroll.workspace.scroll(scroll_name))
    end

    def build_id
      'HELLO'
    end

    def output_dir
      @scroll.artifact_dir
    end

    def source_tmpl
      @source_tmpl ||= @scroll.root / 'source.yaml.erb'
    end

    def source
      @source ||= (
        require_relative '../util'
        YAML.safe_load ERB
          .new(source_tmpl.read, 0, '%')
          .result(binding)
      )
    end

    def source_path
      Pathname.new(source&.dig('name') || 'source.json')
    end

    def inject(builder_def)
      @inject ||= builder_def
        .merge(
          'output_dir' => output_dir.to_s,
          'skip_add' => false,
        )
        .freeze
    end

    def artifact(_)
      @artifact ||= (output_dir / 'package.box')
    end
  end
end
